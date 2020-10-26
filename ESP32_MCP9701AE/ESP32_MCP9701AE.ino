/*ESP32+MCP9701AE,来侦测环境温度。
 * 传感器MCP9701AE和MCP9700的参数是不一样的，需要注意。
 * 按照手册说明，计算公式：Vout = Tc*Ta+V0°C
 * Ta:环境温度,是我们需要计算出来的。
 * Tc:温度系数，查datasheet，是19.5mV/°C。
 * V0°C:0°C的电压,查datasheet，是400mV。
 * Vout测量到的电压输出。
 * ESP32的AD是12位的，所以AnalogRead的结果/4096*3300得到Vout
 * 作者：Bloomlj，2020年10月26
*/
#define tmpADPin 35
double tmp;
void setup() {
  Serial.begin(115200);
  pinMode(tmpADPin,INPUT);
}

void loop() {
  int RawValue = analogRead(tmpADPin);
  double Vout = (RawValue / 4096.0) * 3270; // 单位mV.参考电压3300，需要根据实际情况来修正。
  double tempC = (Vout - 0.4)/19.5;
  Serial.println(tempC);
}
