#include<SoftwareSerial.h>
SoftwareSerial MCU(10,11);

#define NC_Relay 2
#define NO Relay 3

#define AVolt A0
#define ACrnt A1

char State = 'R'; //S -Set, R -Reset 

void setup() {
  Serial.begin(9600);
  Serial.println("Started...!");
  MCU.begin(9600);  
  pinMode(NO_Relay,OUTPUT);
  pinMode(NC_Relay,OUTPUT);
  
  Reset();
}

void loop() {
  int Voltage = analogRead(AVolt);
  int Current = analogRead(ACrnt);
   
  Serial.println("Voltage = "+String(Voltage));
  Serial.println("Current = "+String(Current));

  if(Current >= 5000 or Voltage >= 280){
    Trip();
    }

  if(Serial.available()>0){
    char c = Serial.read();
    if(c == 'T'){
      Trip();
      }
    if(c == 'R'){
      Reset();
      
      }
    
    }
  MCU.print("V"+String(Voltage)+"I"+String(Current)+'S'+State);
}

void Trip(){
    digitalWrite(NC_Relay,HIGH);
    delay(500);
    digitalWrite(NC_Relay,HIGH);
    State = 'R';
  
  }


void Reset(){
    digitalWrite(NO_Relay,HIGH);
    delay(500);
    digitalWrite(NO_Relay,HIGH);
    State = 'S';
  
  }
