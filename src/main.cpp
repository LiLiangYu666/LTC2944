#include <LTC2944.h>

const unsigned int fullCapacity = 4500; // Maximum value is 22000 mAh

LTC2944 gauge(50);      // Takes R_SENSE value (in milliohms) as constructor argument, can be omitted if using CJMCU-294

void setup() {
  Serial.begin(9600);
  Serial.println("LTC2944 Battery Readings Example");
  Serial.println();

  Wire.begin();

  while (gauge.begin() == false) {
    Serial.println("Failed to detect LTC2944!");
    delay(5000);
  }

  gauge.setBatteryCapacity(fullCapacity);
  gauge.setBatteryToFull(); // Sets accumulated charge registers to the maximum value
  gauge.setADCMode(ADC_MODE_SLEEP); // In sleep mode, voltage and temperature measurements will only take place when requested
  gauge.startMeasurement();
}

void loop() {
  unsigned int raw = gauge.getRawAccumulatedCharge();   //原始累计费用
  Serial.print(F("Raw Accumulated Charge: "));
  Serial.println(raw, DEC);

  float ChargingCapacity = gauge.getChargingCapacity();   //电量
  Serial.print(F("Battery Capacity: "));
  Serial.print(ChargingCapacity, 3);
  Serial.println(F(" mAh"));

  float capacity = gauge.getRemainingCapacity();          //剩余容量
  Serial.print(F("Battery Capacity: "));
  Serial.print(capacity, 3);
  Serial.print(F(" / "));
  Serial.print(fullCapacity, DEC);
  Serial.println(F(" mAh"));

  float current = gauge.getCurrent();                    //电流
  Serial.print(F("Current: "));
  Serial.print(current, 3);
  Serial.println(F(" A"));

  float voltage = gauge.getVoltage();                   //电压
  Serial.print(F("Voltage: "));
  Serial.print(voltage, 3);
  Serial.println(F(" V"));

  float temperature = gauge.getTemperature();           //温度
  Serial.print(F("Temperature: "));
  Serial.print(temperature, 2);
  Serial.println(F(" 'C"));

  Serial.println();

  delay(1000);

}