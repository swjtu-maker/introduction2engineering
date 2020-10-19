/*
  LoRa Node With and MCP9701A
  MCU：ESP32-S
  Lora: ai-tinker RA-02 sx1278 470 
  Tempture Sensor:MCP9701A
  created 2020.8.25
  by Bloomlj
*/

#include <LoRaNow.h>

//vspi for lora radio module
#define MISO 19
#define MOSI 23
#define SCK 18
#define SS 5

#define DIO0 4

//for TMP Sensor,MCP9701A
#define tmpADPin 35
double tmp;

void setup() {
  Serial.begin(115200);
  Serial.println("LoRaNow Simple Node");
  pinMode(tmpADPin,INPUT);

   LoRaNow.setFrequencyCN(); // Select the frequency 486.5 MHz - Used in China
  // LoRaNow.setFrequencyEU(); // Select the frequency 868.3 MHz - Used in Europe
  // LoRaNow.setFrequencyUS(); // Select the frequency 904.1 MHz - Used in USA, Canada and South America
  // LoRaNow.setFrequencyAU(); // Select the frequency 917.0 MHz - Used in Australia, Brazil and Chile

  // LoRaNow.setFrequency(frequency);
  // LoRaNow.setSpreadingFactor(sf);
  // LoRaNow.setPins(ss, dio0);

   LoRaNow.setPinsSPI(SCK, MISO, MOSI, SS, DIO0); // Only works with ESP32

  if (!LoRaNow.begin()) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }

  LoRaNow.onMessage(onMessage);
  LoRaNow.onSleep(onSleep);
  LoRaNow.showStatus(Serial);
}

void loop() {
  tmp = readTMP();
  LoRaNow.loop();
}

double readTMP()
{
  int RawValue = analogRead(tmpADPin);
  //Serial.println(RawValue);
  double Voltage = (RawValue / 2048.0) * 3300; // 5000 to get millivots.
  double tempC = Voltage * 0.1;
  //Serial.println(tempC);
  return tempC;
}

void onMessage(uint8_t *buffer, size_t size)
{
  Serial.print("Receive Message: ");
  Serial.write(buffer, size);
  Serial.println();
  Serial.println();
}

void onSleep()
{
  Serial.println("Sleep");
  delay(5000); // "kind of a sleep"
  Serial.println("Send Message");
  LoRaNow.print("LoRaNow Node Message ");
  //Serial.println("LoRaNow Message sended");
  LoRaNow.print(millis());
  LoRaNow.print("-");
  LoRaNow.print(tmp);
  LoRaNow.send();
}
