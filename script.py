#Importing Libraries
import serial
import string
import time
import datetime
import subprocess

#Arduino Serial Connection
ser=serial.Serial("/dev/ttyACM0",115200)

#Variable Declaration
i=0

f= open("raw_data.txt",'w').close()

while i<15:
 #print("****************************")
 serialdata=ser.readline()
 #print(serialdata)
 #String Format Conversion
 string=serialdata.decode('UTF-8')
 #print(string)
 t=datetime.datetime.now()
 #print(t) 
 #Time String Format Conversion 
 time1=t.strftime("%b-%d-%Y\t%H:%M:%S")
 #print(time)
 data= string.rstrip()+"\t"+time1+"\n"
 print(data)
 #print("////////////////////////////")

 #Writing Data for Serial Data in file
 f= open("raw_data.txt","a")
 f.write(data)
 f.close()
 #Iterative Increment
 i=i+1

time.sleep(1)

subprocess.run(["/home/owais/MyProject/config.sh", "arguments"], shell=True)
