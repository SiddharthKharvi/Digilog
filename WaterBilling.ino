#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial MCU(11, 12);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TriA 9

#define EcoA 4
#define EcoB 5
#define EcoC 6
#define EcoD 7
//#define EcoE 8

#define SolA 14
#define SolB 8
#define SolC 16
#define SolD 13

#define WaterFlowA 2
#define WaterFlowB 3

#define Counter

int WaterConA = 0, WaterConB = 0, WaterConC = 0, WaterConD = 0; //Water Consumption (Liters)
int WLevelA = 0, WLevelB = 0, WLevelC = 0, WLevelD = 0, WLevelE = 0; //Water Level (%)
int WaterConSA = 0, WaterConSB = 0;
long ATON = 0, BTON = 0, CTON = 0, DTON = 0;
long ATOFF = 0, BTOFF = 0, CTOFF = 0, DTOFF = 0;
long TimeA = 0, TimeB = 0, TimeC = 0, TimeD = 0;
int UpLimit = 70;
int DownLimit = 20 ;

long ecotime = 0;
int distance = 0;

bool AF = false, BF = false, CF = false, DF = false;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  MCU.begin(9600);
  //MCU.print("A0B0C0D0");
  lcd.begin();
  lcd.backlight();
  lcd.print("INITIALIZING...");

  pinMode(TriA, OUTPUT);
  //pinMode(TriB, OUTPUT);
  //pinMode(TriC, OUTPUT);
  //pinMode(TriD, OUTPUT);
  //pinMode(TriE, OUTPUT);

  pinMode(EcoA, INPUT);
  pinMode(EcoB, INPUT);
  pinMode(EcoC, INPUT);
  pinMode(EcoD, INPUT);
  //pinMode(EcoE, INPUT);


  pinMode(SolA, OUTPUT);
  pinMode(SolB, OUTPUT);
  pinMode(SolC, OUTPUT);
  pinMode(SolD, OUTPUT);


  digitalWrite(SolA, HIGH);
  digitalWrite(SolB, HIGH);
  digitalWrite(SolC, HIGH);
  digitalWrite(SolD, HIGH);
  delay(1000);

  digitalWrite(14, LOW);
  digitalWrite(10, LOW);
  digitalWrite(16, LOW);
  digitalWrite(13, LOW);

}

void loop() {
  WaterLevel();

  lcd.setCursor(0, 0);
  lcd.print("A:" + String(AF) + " B:" + String(BF) + " C:" + String(CF) + " D:" + String(DF));
  lcd.setCursor(0, 1);
  lcd.print(String(WaterConA));
  lcd.setCursor(4, 1);
  lcd.print(String(WaterConB));
  lcd.setCursor(8, 1);
  lcd.print(String(WaterConC));
  lcd.setCursor(12, 1);
  lcd.print(String(WaterConD));


  //TURN ON A
  if (WLevelA <= DownLimit && AF == false && BF == false) {
    AF = true;
    WaterConSA = 0;

    Serial.println("A ON");
    ATON = millis();
    Serial.println("ATON:"+String(ATON));
    

  }

  //TURN OFF A
  if (WLevelA >= UpLimit && AF == true) {
    AF = false;
    //WaterConA = WaterConSA ;
    ATOFF = millis();
    Serial.println("ATOFF:"+String(ATOFF));
    TimeA = ATOFF - ATON;
    WaterConA = map(TimeA,0,61000,0,600);
    Serial.println("TIMEA:"+String(TimeA));
    Serial.println("WA: " + String(WaterConA));
    MCU.println('A' + String(WaterConA));
    MCU.println('A' + String(WaterConA));
    MCU.println('A' + String(WaterConA));

    Serial.println("A OFF");

  }

  //TURN ON B
  if (WLevelB <= DownLimit && BF == false && AF == false) {
    BF = true;
    WaterConSA = 0;


    Serial.println("B ON");
    BTON = millis();
  }

  //TURN OFF B
  if (WLevelB >= UpLimit && BF == true) {
    BF = false;
    WaterConB = WaterConSA ;
    Serial.println("WB: " + String(WaterConB));
    Serial.println("B OFF");
    BTOFF = millis();
    TimeB = BTOFF - BTON;
    WaterConB = map(TimeB,0,93000,0,600);
    Serial.println("TIMEB:"+String(TimeB));
    
    MCU.println('B' + String(WaterConB));
    MCU.println('B' + String(WaterConB));
    MCU.println('B' + String(WaterConB));
    

  }

  //TURN ON C
  if (WLevelC <= DownLimit && CF == false && DF == false) {
    CF = true;
    WaterConSB = 0;
    Serial.println("C ON");
    CTON = millis();
  }

  //TURN OFF C
  if (WLevelC >= UpLimit && CF == true) {
    CF = false;
    WaterConC = WaterConSB;
    Serial.println("WC: " + String(WaterConC));
    
    CTOFF = millis();
    TimeC = CTOFF - CTON;
    WaterConC = map(TimeC,0,103000,0,600);
    Serial.println("TIMEC:"+String(TimeC));
    MCU.println('C' + String(WaterConC));
    MCU.println('C' + String(WaterConC));
    MCU.println('C' + String(WaterConC));

    Serial.println("C OFF");
  }

  //TURN ON D
  if (WLevelD <= DownLimit && DF == false && CF == false) {
    DF = true;
    WaterConSB = 0;

    Serial.println("D ON");
    DTON = millis();
  }

  //TURN OFF D
  if (WLevelD >= UpLimit && DF == true) {
    digitalWrite(SolD, LOW);
    DF = false;
    
    DTOFF = millis();  
    TimeD = DTOFF - DTON;
    WaterConD = map(TimeD,0,88000,0,600);
    Serial.println("TIMED:"+String(TimeD));
    Serial.println("WD: " + String(WaterConD));
    MCU.println('D' + String(WaterConD));
    MCU.println('D' + String(WaterConD));
    MCU.println('D' + String(WaterConD));

    Serial.println("D OFF");
    DTOFF = millis();
    DTOFF - DTON;
  }

  digitalWrite(SolA, AF);
  digitalWrite(SolB, BF);
  digitalWrite(SolC, CF);
  digitalWrite(SolD, DF);


  delay(100);
  MCU.print('A' + String(WaterConA) + 'B' + String(WaterConB) + 'C' + String(WaterConC) + 'D' + String(WaterConD));
//  Serial.println("Status:");
//  Serial.print(AF);
//  Serial.print(BF);
//  Serial.print(CF);
//  Serial.print(DF);
//  Serial.println("-");

}

void WaterLevel() {
  //----------------------------------------------- A

  digitalWrite(TriA, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriA, LOW);

  ecotime = pulseIn(EcoA, HIGH);
  distance = ecotime * 0.034 / 2;
  WLevelA = map(distance, 13, 1, 0, 100);
  //Serial.println("A: " + String(distance) + "cm : " + String(WLevelA));

  delay(500);

  //------------------------------------------------- B

  digitalWrite(TriA, HIGH);
  delayMicroseconds(20);
  digitalWrite(TriA, LOW);

  ecotime = pulseIn(EcoB, HIGH);
  distance = ecotime * 0.034 / 2;
  WLevelB = map(distance, 13, 1, 0, 100);
  //Serial.println("B: " + String(distance) + "cm : " + String(WLevelB));
  delay(500);

  //------------------------------------------------- C
  digitalWrite(TriA, HIGH);
  delayMicroseconds(20);
  digitalWrite(TriA, LOW);

  ecotime = pulseIn(EcoC, HIGH);
  distance = ecotime * 0.034 / 2;
  WLevelC = map(distance, 13, 1, 0, 100);
  //Serial.println("C: " + String(distance) + "cm : " + String(WLevelC));
  delay(500);

  //------------------------------------------------- D

  digitalWrite(TriA, HIGH);
  delayMicroseconds(20);
  digitalWrite(TriA, LOW);

  ecotime = pulseIn(EcoD, HIGH);
  distance = ecotime * 0.034 / 2;
  WLevelD = map(distance, 13, 1, 0, 100);
  ///Serial.println("D: " + String(distance) + "cm : " + String(WLevelD));
  delay(500);

  //------------------------------------------------- E
  //  digitalWrite(TriA, HIGH);
  //  delayMicroseconds(20);
  //  digitalWrite(TriA, LOW);
  //
  //  ecotime = pulseIn(EcoE, HIGH);
  //  distance = ecotime * 0.034 / 2;
  //  WLevelE = map(distance, 13, 1, 0, 100);
  //  Serial.println("E: " + String(distance) + "cm : " + String(WLevelE));
  //  delay(500);
 
}
