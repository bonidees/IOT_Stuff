
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLJmpAUome"
#define BLYNK_DEVICE_NAME "Fire Starter"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define pin_SDA                         21
#define pin_SCL                         22
#define BME280_I2C_ADDRESS 0x76


#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7

#include "BlynkEdgent.h"
#include "SparkFunBME280.h"
#include "wire.h"
#include <SPI.h>

BME280 BME280_sensor;
BlynkTimer timer;


void sendSensor()
{
  float t = BME280_sensor.readTempF(); 
  float h = BME280_sensor.readFloatHumidity();

  if (isnan(h) || isnan(t)) {
   // Serial.println("Failed to read from BME sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more than 10 values per second.
  Serial.println("Temp:" );
  Serial.print(t);
  Serial.println("Humidity: ");
  Serial.print(h);

 Serial.println("Sending Sensor Values to Blynk..." );
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
 



//TO DO 5
  
 // Blynk.syncVirtual(V0,V1);
  //Serial.println(V0);
 // Serial.println(V1);
   

}

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  Wire.setPins(pin_SDA, pin_SCL);
Wire.begin();

// init BME280
BME280_sensor.setI2CAddress(BME280_I2C_ADDRESS);
BME280_sensor.beginI2C();

timer.setInterval(60000L, sendSensor);


}

void loop() {
  BlynkEdgent.run();

   if(Blynk.connected()){
 delay(500);
 Blynk.run();
 timer.run();
 } else  Serial.print("Trying to connect again... ");



}
