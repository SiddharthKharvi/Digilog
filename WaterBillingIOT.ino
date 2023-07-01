#include "thingProperties.h"
int cons = 0;
#define LED D0
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  if (Serial.available()) {
    digitalWrite(LED,LOW);
    char c = Serial.read();
    if (c == 'A') {
      cons = Serial.parseInt();
      bill_A = "Water Consumed: " + String(cons) + "ml Cost:" + String(cons * 2) + "Rs";
      last_con = cons;
    }

    if (c == 'B') {
      cons = Serial.parseInt();
      bill_B = "Water Consumed: " + String(cons) + "ml Cost:" + String(cons * 2) + "Rs";
      last_con = cons;
    }

    if (c == 'C') {
      cons = Serial.parseInt();
      bill_C = "Water Consumed: " + String(cons) + "ml Cost:" + String(cons * 2) + "Rs";
      last_con = cons;
    }

    if (c == 'D') {
      cons = Serial.parseInt();
      bill_D = "Water Consumed: " + String(cons) + "ml Cost:" + String(cons * 2) + "Rs";
      last_con = cons;
    }
    digitalWrite(LED,HIGH);
    delay(500);
  }
  
}

/*
  Since BillA is READ_WRITE variable, onBillAChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBillAChange()  {
  // Add your code here to act upon BillA change
}
/*
  Since BillB is READ_WRITE variable, onBillBChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBillBChange()  {
  // Add your code here to act upon BillB change
}
/*
  Since BillC is READ_WRITE variable, onBillCChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBillCChange()  {
  // Add your code here to act upon BillC change
}
/*
  Since BillD is READ_WRITE variable, onBillDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBillDChange()  {
  // Add your code here to act upon BillD change
}
/*
  Since LastCon is READ_WRITE variable, onLastConChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLastConChange()  {
  // Add your code here to act upon LastCon change
}
