//Libraries  and Variables Declaration
#include <TH02_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"
#define ShowSerial Serial

#ifdef __AVR__
    #include <SoftwareSerial.h>
    SoftwareSerial SSerial(2, 3); // RX, TX
    #define COMSerial Serial
    #define ShowSerial Serial
    TH02_dev TH02;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define COMSerial Serial1
    #define ShowSerial SerialUSB
    TH02_dev TH02;
#endif

#ifdef ARDUINO_ARCH_STM32F4
    #define COMSerial Serial
    #define ShowSerial SerialUSB
    TH02_dev TH02;
#endif

int LED=2;  
int PIR=3; 
int PR=A0;
int WS=A1;

int PIR_status=0;
int PR_value=0;
int WS_value=0;

/*************************************/


void setup() 
{
    pinMode(LED,OUTPUT);
    pinMode(PIR,INPUT); 

    TH02.begin();
    delay(100);
    //Serial.println("TH02_dev is available.\n");
    
    Serial.begin(115200);
    Serial.println("");
    //Serial.println("Setup Initialized!");
}


void loop() 
{  
    //Serial.print("\r");
    //Temperature and Humidity Monitoring
    /******************************/
    float temp = TH02.ReadTemperature();
    Serial.print("T: ");
    Serial.print(temp);
    Serial.print("C");
    Serial.print("\t");
    //Serial.print("%\t");
    float humidity = TH02.ReadHumidity();
    Serial.print("H: ");
    Serial.print(humidity);
    Serial.print("%");
    //Serial.print("%\r\n");
    Serial.print("\t");
    /******************************/

    //Illuminance Status
   /******************************/
   
    
   PR_value=analogRead(PR);

   Serial.print("Illum: ");
   //Serial.println(PR_value);

   if (PR_value < 10) 
   {
    Serial.print("Dark");
   } 
   else if (PR_value < 200) 
   {
    Serial.print("Dim");
   } 
   else if (PR_value < 500) 
   {
    Serial.print("Light");
   } 
   else if (PR_value < 800) 
   {
    Serial.print("Bright");
   } 
   else 
   {
    Serial.print("Very Bright");
   }
  /******************************/
    Serial.print("\t");
    
   //Raining Status or Water Uprising
   /******************************/
   WS_value=analogRead(WS);
   //Serial.print("WS_Value: ");
   //Serial.print(WS_value);
   Serial.print("RS: ");
   if (WS_value >900)
   {
    Serial.print("No Rain!");
   }
   else if (WS_value < 900 && WS_value > 400)
   {
    Serial.print("Light Rain!");
   }
   else if (WS_value < 400)
   {
    Serial.print("Heavy Rain!");
   }
   /******************************/
   
   //Movement Detection
   /******************************/
   PIR_status = digitalRead(PIR);
   
   //Serial.print("PIR_Status: ");
   //Serial.print(PIR_status);
   Serial.print("\t");

   Serial.print("Obj: ");
   if (PIR_status == HIGH )
   {
    Serial.println("Movement Detected!");
    digitalWrite(LED,HIGH);
   }
   else
   {
    Serial.println("No Movement!");
    digitalWrite(LED,LOW);
   }
   /******************************/
   delay (5000);
  
}
