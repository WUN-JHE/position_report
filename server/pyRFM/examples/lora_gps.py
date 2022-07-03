from datetime import datetime
import pynmea2
import pymysql
import sys
import os
#!/usb/bin/env python

"""
    waits for incomming message and sends response
"""
__author__  = """Alexander Krause <alexander.krause@ed-solutions.de>"""
__date__        = "2016-12-28"
__version__ = "0.1.0"
__license__ = "GPL"
import logging
import array

sys.path.append(
    os.path.join(
        os.path.dirname(__file__),
        '..'
    )
)
    
import lib as pyrfm
conf={
    'll':{
        'type':'rfm95'
    },
    'pl':{
        'type': 'serial_seed',
        'port': '/dev/ttyUSB0'
    }
}
ll=pyrfm.getLL(conf)
count=0

'''----------------------'''
logging.basicConfig(level=logging.DEBUG,format='%(asctime)s %(levelname)s %(message)s',datefmt='%Y-%m-%d %H:%M',handlers=[logging.FileHandler('farmer_nanhua.log','w','utf-8')])

print('HW-Version: ', ll.getVersion())
print('Lora test is completed! Waiting for Sensors Data............')
if ll.setOpModeSleep(True,True):
    ll.setFiFo()
    ll.setOpModeIdle()
    ll.setModemConfig('Bw125Cr45Sf128');
    ll.setPreambleLength(8)
    ll.setFrequency(905)
    ll.setTxPower(13)
    
    while True:
        #   ll.sendStr('Hello world!')
    #   ll.waitPacketSent()
        try:
            if ll.waitRX(timeout=2):
                data=ll.recv()
                header=data[0:4]
                msg=data[4:]
                number = data[4]
                # print('header: ',header)
                print("")
                print('message:',msg)
                if len(msg)==65:
                    gps = ''
                    count = 0
                    for i in range(5,69):
                        '''if(chr(data[i])=='$'):
                            count = count + 1
                        if(count <= 1):'''
                        gps = gps + chr(data[i])
                    print(number)
                    print(gps)
                    print(datetime.now())
                    for i in range(len(gps)):
                        if gps[i] == '$' and gps[i+1] == 'G' and gps[i+2] == 'P' and gps[i+3] == 'G' and gps[i+4] == 'G' and gps[i+5] == 'A':
                            gps_split = gps.split(',')
                            #print(gps_split)
                            if gps_split[3] == "N" or gps_spliit[3] == "S" or gps_split[5] == "E" or gps_split[5] == "W":
                                '''print(gps_split[2][0:2])
                                print(gps_split[2][2:9])
                                print(gps_split[4][0:3])
                                print(gps_split[4][3:10])'''
                                lat = float(gps_split[2][0:2]) + ( float(gps_split[2][2:9]) / 60 )
                                lng = float(gps_split[4][0:3]) + ( float(gps_split[4][3:10]) / 60 )
                                print("lat:{:.6f} lng:{:.6f} ".format(lat,lng))
                                now = datetime.now()
                                time = now.strftime('%Y-%m-%d %H:%M:%S')
                                fp = open("gps_log.txt","a")
                                fp.write("{} {:.6f} {:.6f}\n".format(time , lat , lng))
                                fp.close()
                                #mysql section

                                db = pymysql.connect(host='140.116.226.204',port=3306,user='mmn',passwd='mmnmmnlab',db='POS_REP',charset='utf8')
                                cursor = db.cursor()
                                sql = "INSERT INTO member_{}(time,lat,lng)VALUES(%s,{},{})".format(str(number),lat,lng)
                                cursor.execute(sql,time)
                                db.commit()
                                db.close()
        except Exception as e:
            print(e)
            logging.error(e)
            
            
