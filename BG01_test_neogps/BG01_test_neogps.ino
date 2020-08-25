/*
BG-01 Beidou Module TEST
*/

#include <HardwareSerial.h>
HardwareSerial SerialBD(1);

#include <NMEAGPS.h>
NMEAGPS gps;
gps_fix fix;


void setup() {
  Serial.begin(115200);
  SerialBD.begin(9600,SERIAL_8N1,5,18);//5 rx,18 tx
}


void loop()
{
//   if(SerialBD.available()){
//      Serial.print(char(SerialBD.read()));
//   }
   
  if (gps.available( SerialBD )) {
    fix = gps.read();
    
    //0 STATUS_NONE, 1 STATUS_EST, 2 STATUS_TIME_ONLY, 3 STATUS_STD or 4 STATUS_DGPS  
    Serial.print("status:");
    Serial.println(fix.status);  
    Serial.print("longitude:");
    Serial.println(fix.longitude());
    Serial.print("latitude:");
    Serial.println(fix.latitude());
    
    Serial.print("altitude:");
    Serial.println(fix.altitude());
    Serial.print("speed:");
    Serial.println(fix.speed_kph());
    Serial.print("satellites count:");
    Serial.println(fix.satellites);
    char timestring[16];
    sprintf(timestring,"%d-%d-%d-%d:%d:%d",fix.dateTime.year,fix.dateTime.month,fix.dateTime.date,fix.dateTime.hours,fix.dateTime.minutes,fix.dateTime.seconds);
    
    Serial.print("UTC "); 
    Serial.println(timestring);
    Serial.print(fix.dateTime.year);
    Serial.print("-"); 
    Serial.print(fix.dateTime.month);
    Serial.print("-"); 
    Serial.print(fix.dateTime.date);
    Serial.print(" "); 
    Serial.print(fix.dateTime.hours);
    Serial.print(":"); 
    Serial.print(fix.dateTime.minutes);
    Serial.print(":"); 
    Serial.println(fix.dateTime.seconds);   
  }
}
