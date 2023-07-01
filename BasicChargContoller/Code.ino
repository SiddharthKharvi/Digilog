#include <LiquidCrystal.h>

const int rs = 2, en = 4, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Voltage = 0;
float V = 0.0;
float SV = 0.0;
void setup() {
  lcd.begin(16, 2);
  lcd.print("INITIALIZING");
  lcd.setCursor(0, 1);
  lcd.print("ChargeController");
  Serial.begin(9600);
  delay(1500);
}

void loop() {

  V = ((float)analogRead(A4) / (1024.0 / 5.0)) * 2;

  SV = ((float)analogRead(A3) / (1024.0 / 5.0)) * 2;

  lcd.clear();
  lcd.print("Battery :" + String(V) + "V");
  lcd.setCursor(0, 1);
  V = V * 100;
  int PR = map(V, 6.0 * 100, 7.5 * 100, 0, 100);
  if (PR <= 0) {
    PR = 0;

  }
  lcd.print("Charge: " + String(PR) + "%" );

  delay(2000);

  lcd.clear();
  lcd.print("Solar:" + String(SV) + "V");
  if (BV <= 4.0) {
    digitalWrite(20, HIGH);

  }
  else {
    digitalWrite(20, LOW);
  }

  
  if (SV >= 4) {
    lcd.setCursor(0, 1);
    lcd.print("CHARGING...");

  }
  delay(2000);


}

void ReadVolt() {


}
