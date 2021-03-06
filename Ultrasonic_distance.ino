//Load SPI and SD library  
#include <SPI.h>  
#include <SD.h>  
  
//Declare File object  
File myFile; 

#define Trig 2 
#define Echo 3 

float cm; 
float temp; 
unsigned long cur_time;
  
void setup()   
{  
    Serial.begin(9600); 
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);  
    
    while (!Serial)   
    {  
    ; // wait for serial port to connect. Needed for native USB port only  
    }  
      
    Serial.print("Initializing SD card...");
   
    if (!SD.begin(4)) {  
      Serial.println("initialization failed!");  
      return;  
    }  
    Serial.println("initialization done.");

    SD.remove("LSLAB.txt");
}  
  
void loop() {  
  digitalWrite(Trig, LOW); 
  delayMicroseconds(2);    
  digitalWrite(Trig,HIGH); 
  delayMicroseconds(10);   
  digitalWrite(Trig, LOW); 
  
  temp = float(pulseIn(Echo, HIGH));
  
  cm = (temp * 17 )/1000; //Convert to cm

  myFile = SD.open("EXP.txt", FILE_WRITE);

  Serial.print("Echo =");
  Serial.print(temp);
  Serial.print(" | | Distance = ");
  Serial.print(cm);
  cur_time = micros();
  myFile.print(cur_time);
  myFile.print(", ");
  myFile.println(cm);
  Serial.println("cm");
  delay(30);
  myFile.close();
  
}  
