#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(2, 3);
uint8_t buffer[64];                   // buffer array for data receive over serial port
int count=0;                                // counter for buffer array



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
    SoftSerial.begin(9600);                 // the SoftSerial baud rate
    //Serial.begin(9600);                     // the Serial port of Arduino baud rate.

    rf95.init();
    rf95.setFrequency(905);
}
 
void loop()
{
    char data[65];
    uint8_t lora_data[65];
    if (SoftSerial.available())                     // if date is coming from software serial port ==> data is coming from SoftSerial shield
    {
        while(SoftSerial.available())               // reading data into char array
        {
            buffer[count++]=SoftSerial.read();      // writing data into array
            if(count == 64)break;
        }
        char gps[64] = "$GPGGA,055148,2407.8945,N,12041.7649,E,1,00,1.0,155.2,M,16.6,M,X.X,xxxx,*47";
        for(int i = 1; i < 65 ; i++ )
        {
            lora_data[i] = buffer[i-1];
        }
        
        //Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
        //clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array
        count = 0;                                  // set counter of while loop to zero 
        clearBufferArray();
        
    }
    //if (Serial.available())                 // if data is available on hardware serial port ==> data is coming from PC or notebook
    //SoftSerial.write(Serial.read());        // write it to the SoftSerial shield
    
    //Serial.print(data);
    char *result[100]; 
    char *p = strtok(data , ",");
    int count = 0;
    float lat,lng;
    for( int i = 0 ; i < 5 ; i++ )
    {
        //lora_data[i]='0';
    }
    while( p != NULL )
    {
      result[count++] = p;
      p = strtok(NULL , ",");
    }
    /*if( count <= 10 )
    {
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
      
    }*/
    


    lora_data[0]= int(3);
    rf95.send(lora_data, sizeof(lora_data));
    rf95.waitPacketSent();
    delay(5000);
}
 
 
void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    {
        buffer[i]=NULL;
    }                      // clear all index of array with command NULL
}
