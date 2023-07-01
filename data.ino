#include<ESP8266WiFi.h>
#include "Thingspeak.h"

char ssid[] ="MySSID";
char pass[] ="MySSID";

WiFiClient client;

unsigned long CN1 = 000000;
const char * API1 = "Skjdb hdufbkbjvhkv ll";

unsigned long CN2 = 000000;
const char * API2 = "Skjdb hdufbkbjvhkv ll";

void setup(){
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    Thingspeak.begin(client);

 
}

void loop(){
   if(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid,pass);
        Serial.println(".");
        delay(1000);
    }

    if(Serial.available()){
        char c = Serial.read();
        if(c == 'M'){
            int Moist = Serail.read();
            ThingSpeak.writeField(CN1, 1, Moist, API1);
  

        }

        if(c == 'T'){
            Temp = Serail.read();
            ThingSpeak.writeField(CN1, 2, Temp, API1);
  
        }

        if(c == 'W'){
            int WCon = Serial.read();
            
            int x =0;
            while(x != 200){
                x = ThingSpeak.writeField(CN1, 3, WCon, API1);
            
            }

            x = 0;
            while(x != 200){
                x = ThingSpeak.writeField(CN2, 3, WCon, API2);
            
            } 
        }
    }
}



