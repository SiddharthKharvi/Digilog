#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

boolean result[41]; //holds the result
unsigned int temp; //in celcius
//unsigned int humidity; //in %RH

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int data_pin = 17;
OneWire oneWire(data_pin);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

int SetTemprature = 0;
int dustLevel1 = 0, dustLevel2 = 0;


void setup() {
  lcd.begin(16, 2);

  Serial.begin(9600);
  sensors.begin();

  pinMode(8, OUTPUT);
  digitalWrite(8, 1);
  pinMode(18, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, 1);
  digitalWrite(12, 1);

  digitalWrite(18, HIGH);
  lcd.print("INITIALIZING...");

  delay(2000);
}

void loop() {
  getDust();
  lcd.clear();
  lcd.print("DUST INLET: " + String(dustLevel1));
  lcd.setCursor(0, 1);
  lcd.print("DUST OUTLET: " + String(dustLevel2));
  Serial.println("*A"+String(dustLevel1)+"*");
  Serial.println("*B"+String(dustLevel2)+"*");
  delay(2000);

  readTemp();
  lcd.clear();
  lcd.print("TEMPERATURE: " + String(temp) + "'C");
  lcd.setCursor(0, 1);
  lcd.print("SET TEMP: " + String(SetTemprature) + "'C");
  delay(2000);

  getSerial();
  Actuate();


}


void getDust() {
  digitalWrite(18, LOW);
  delayMicroseconds(280);
  dustLevel1 = analogRead(A1);
  delayMicroseconds(40);
  digitalWrite(18, HIGH);

  delay(1000);

  digitalWrite(18, LOW);
  delayMicroseconds(280);
  dustLevel2 = analogRead(A0);
  //dustLevel2 = map(dustLevel2 ,0,1023,0,50);
  delayMicroseconds(40);
  digitalWrite(18, HIGH);
}


void readTemp() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  temp = int(tempC);
  Serial.print("*T" + String(temp) + "*");

}

void getSerial() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'T') {
      SetTemprature = Serial.parseInt();
      lcd.clear();
      lcd.print("SET TEMP" + String(SetTemprature));
      delay(1000);
    }
  }
}

void Actuate() {
  if (SetTemprature >= 22) {
    lcd.clear();
    if (temp <= SetTemprature - 1) {
      lcd.print("HEATING.");
      Serial.println("*H*");
      digitalWrite(11, 0);
      delay(2000);
    }
    else {
      digitalWrite(11, 1);
      Serial.println("*h*");
    }

    if (temp >= SetTemprature + 1) {
      lcd.print("COOLING");
      Serial.println("*C*");
      digitalWrite(12, 0);
      delay(2000);
    }
    else {
      digitalWrite(12, 1);
      Serial.println("*c*");
    }


  }
}
