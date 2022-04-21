#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon). 
char auth[] = "tNhsIEtKqzKRNURN1C03aHk5wF-99NG1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Internet1";
char pass[] = "MyPassword";


WidgetLED led1(V2);
void myEvent(){
  while(Serial.available()>0){
    char c = Serial.read();
    if(c == 'V'){
      int Volt = Serial.parseInt();
      }
    if(c == 'I'){
      int Crnt = Serial.parseInt(); 
      }
    if(c == 'S'){
      char State = Serial.read();
      if(State == 'R'){
        led1.on();
        }
      if(State == 'S'){
        led1.off();
        }
      }   
    }
  
  Blynk.virtualWrite(V0,250);
  Blynk.virtualWrite(V1,11);
  led1.on();
  


  
  }

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,myEvent);

}

void loop()
{
  Blynk.run();
  timer.run();
}
