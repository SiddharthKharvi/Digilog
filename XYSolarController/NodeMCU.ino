#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "Internet1";   // your network SSID (name)
char pass[] = "MyPassword";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long myChannelNumber = 1679998;
const char * myWriteAPIKey = "OFUL3V1VSTLXAZLN";

int number = 0;
int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial
  while (!Serial) {
    ;
  }

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  lcd.init();
  lcd.backlight();

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
      lcd.setCursor(0, 0);
      lcd.print("   WIFI");
      lcd.setCursor(0, 1);
      lcd.print("DISCONNECTED");
    }
    Serial.println("\nConnected.");
    lcd.clear();
  }

  if (Serial.available()) {
    char c = Serial.read();
    Serial.println(c);


    if (c == 'S') {
      int SVolt = Serial.parseInt();
      Serial.println("S: " + String(SVolt));
      lcd.setCursor(0, 0);
      lcd.print("Solar: " + String(SVolt) + "V");

      if (i >= 20) {
        int q = 0;
        q = ThingSpeak.writeField(myChannelNumber, 2, SVolt, myWriteAPIKey);
        i = 0;
      }
      else {
        i++;
      }
    }
    if (c == 'B') {
      int BVolt = Serial.parseInt();
      lcd.setCursor(0, 1);
      lcd.print("Battery: " + String(BVolt) + "V");
      Serial.println("B: " + String(BVolt));
      int p = 0;
      if (j >= 20) {
        p = ThingSpeak.writeField(myChannelNumber, 1, BVolt, myWriteAPIKey);
        Serial.println(p);
        j = 0;
      }
    }
    else {
      j++;    
    }
  }

  delay(100);
}
