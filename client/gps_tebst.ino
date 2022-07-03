//RTC
#include "RTClib.h"
RTC_DS3231 rtc;

//SD
#include <SPI.h>
#include <SD.h>
File myFile;
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 4;

//gps
#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(2, 3);
unsigned char buffer[64];                   
int count=0;                                

//LORA
uint8_t number=0;
#include <RH_RF95.h>
/*#include <SoftwareSerial.h>
SoftwareSerial SSerial(5, 6); // RX, TX
#define COMSerial SSerial
RH_RF95<SoftwareSerial> rf95(COMSerial);
*/
#define COMSerial Serial
#define ShowSerial Serial
RH_RF95<HardwareSerial> rf95(COMSerial);

void setup()
{
  
  //gps
  //SoftSerial.begin(9600);                 // the SoftSerial baud rate
  //Serial.begin(9600);                     // the Serial port of Arduino baud rate.

    //SD
  //----------- 寫入檔案
  //Serial.print("Waiting for SD card ready...");

  if (!SD.begin(4)) 
  {
    //Serial.println("Fail!");
    return;
  }
  //Serial.println("Success!");
  if (!rf95.init()) 
  {
        //Serial.println("init failed");
        //while (1);
  }
  rf95.setFrequency(905);
  delay(1000);
}
 
void loop()
{
    char data[64];
    for(int i = 0 ; i < 64 ; i++ )
    {
      data[i]='x';
    }
    if (SoftSerial.available())
    {
        while(SoftSerial.available())
        {
            buffer[count++]=SoftSerial.read();
            if(count == 64)break;
        }
        for(int i=0;i<64;i++)
        {
          data[i]=buffer[i];
        }
        //Serial.write(buffer,count);
        clearBufferArray();
        count = 0;                                
    }
    //unsigned char buffer1[64] = "$GPGGA,094708.95,3854.930,N,08102.496,W,0,00,,,M,,M,,*6F";
    for(int i=0;i<64;i++)  //將gps資料寫入待傳輸陣列
    {
      data[i]=buffer[i]; //0~17項放感測器資料，從[18]開始放
    }
   
    //Serial.println(data);
    char *result[50]; 
    char *p = strtok(data , ",");
    int count = 0;
    float lat,lng;
    uint8_t lora_data[14];
    DateTime now = rtc.now();
    while( p != NULL )
    {
      result[count++] = p;
      p = strtok(NULL , ",");
    }
    if( count <= 9 )
    {
      //Serial.println("格式錯誤");
      lora_data[0] = 'x';
      lora_data[1] = 'x';
      lora_data[2] = 'x';
      lora_data[3] = 'x';
      lora_data[4] = 'x';
      lora_data[5] = 'x';
      lora_data[6] = 'x';
      lora_data[7] = 'x';
      lora_data[8] = 'x';
      lora_data[9] = 'x';
      lora_data[10] = 'x';
      lora_data[11] = 'x';
      lora_data[12] = 'x';
      lora_data[13] = 'x';
      lora_data[14] = 'y';;
    }
    else
    {
      int lat_count = -1 ;
      int lng_count = -1 ;
      lat = atof(result[2]+2)/60*1000000;
      lat = lat + (int)(result[2][0]-48)*10 + (int)(result[2][1]-48);
      lng = atof(result[4]+3)/60;
      lng = lng + (int)(result[4][0]-48)*100 + (int)(result[4][1]-48)*10 + (int)(result[4][2]-48);
      lora_data[0] = result[2][0]-48;
      lora_data[1] = result[2][1]-48;
      lora_data[2] = result[2][2]-48;
      lora_data[3] = result[2][3]-48;
      
      lora_data[4] = result[2][5]-48;
      lora_data[5] = result[2][6]-48;
      lora_data[6] = result[2][7]-48;

      lora_data[7] = result[4][0]-48;
      lora_data[8] = result[4][1]-48;
      lora_data[9] = result[4][2]-48;
      lora_data[10] = result[4][3]-48;
      lora_data[11] = result[4][4]-48;

      lora_data[12] = result[4][6]-48;
      lora_data[13] = result[4][7]-48;
      lora_data[14] = result[4][8]-48;

      
   
      //lora_data[15]=int(21);  //2021
      //lora_data[16]=int(now.month());
      //lora_data[17]=int(now.day());
      //lora_data[18]=int(now.hour());
      //lora_data[19]=int(now.minute());
    }
    rf95.send(lora_data, sizeof(lora_data));
    rf95.waitPacketSent();
    
    


  myFile = SD.open("test.txt", FILE_WRITE);       // 開啟檔案，一次僅能開啟一個檔案
  
  if (myFile) 
  {
    
         
    //SD_RTC         
    /*myFile.print(now.year(), DEC);  // 繼續寫在檔案後面
    myFile.print("/");
    myFile.print(now.month(), DEC);
    myFile.print("/");
    myFile.print(now.day(), DEC);
    myFile.print(",");
    myFile.print(now.hour(), DEC);
    myFile.print(":");
    myFile.print(now.minute(), DEC);
    myFile.print(":");
    myFile.print(now.second(), DEC);
    myFile.close();                               // 關閉檔案
    //Serial.println("Save Completed!");*/
  } 
  else 
  {
    //Serial.println("\n open file error ");    // 無法開啟時顯示錯誤
  }


  delay(2000);
}
 
 
void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }                      // clear all index of array with command NULL
}
