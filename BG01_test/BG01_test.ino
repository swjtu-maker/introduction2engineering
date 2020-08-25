/*
BD-01 TEST
*/


#include <HardwareSerial.h>
HardwareSerial SerialBD(1);

void setup() {
  Serial.begin(115200);
  SerialBD.begin(9600,SERIAL_8N1,5,18);//5 rx,18 tx
}

void loop() {
  if(SerialBD.available()){
      Serial.print(char(SerialBD.read()));
   }
  //delay(1000);
}
