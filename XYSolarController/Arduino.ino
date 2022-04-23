#include<SoftwareSerial.h>
#include<Servo.h>

SoftwareSerial MCU(11, 10); //Rx,Tx
Servo XServo;
Servo YServo;

#define SlrVlt A2 
#define BatVlt A1
#define LoadRelay A3
//#define  XSense A4
//#define YSense A5


int XSense = 0;
int YSense = 0;

#define LED 9

int SolarVolt = 00;
int BatryVolt = 00;

int BatrymVolt = 6.00;
int SoalrmVolt = 9.00;

float XPos = 145;
float YPos = 145;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MCU.begin(9600);
  XServo.attach(8);
  YServo.attach(7);

  //pinMode(LoadRelay, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);
  digitalWrite(LoadRelay, HIGH);
}

void loop() {
  //INPUT
  BatryVolt = (analogRead(BatVlt)/203) * 3;
  SolarVolt = (analogRead(SlrVlt)/203) * 3;
  XSense = analogRead(A5);
  YSense = analogRead(A4);
  XSense = map(XSense, 0, 1024, 0, 10);
  YSense = map(YSense, 0, 1024, 0, 10);


  // Process
  if (SolarVolt >= 2) {
    digitalWrite(LoadRelay, HIGH);
  }
  else {
    digitalWrite(LoadRelay, LOW);
  }

  if (XSense >= 7 && XPos <= 180) {
    XPos = XPos + 1;
  }
  if (XSense <= 3 && XPos >= 60) {
    XPos = XPos - 1;
  }

  if (YSense >= 7 && YPos <= 180) {
    YPos = YPos + 1;
  }

  if (YSense <= 3 && YPos >= 60) {
    YPos = YPos - 1;
  }



  //OUTPUT
  XServo.write(XPos);
  YServo.write(YPos);

  MCU.println('S' + String(SolarVolt));
  MCU.println('S' + String(SolarVolt));
  MCU.println('B' + String(BatryVolt));

  Serial.println("S -> " + String(SolarVolt));
  Serial.println("B -> " + String(BatryVolt));
  Serial.println("XPos:" + String(XPos));
  Serial.println("YPos:" + String(YPos));
  Serial.println("XSens:" + String(XSense));
  Serial.println("YSens:" + String(YSense));
  delay(100);
 }
