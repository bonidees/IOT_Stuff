
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLJmpAUome"
#define BLYNK_DEVICE_NAME "Fire Starter"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
//#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <BME280I2C.h>
#include <Wire.h>

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

BlynkTimer timer;

int LED = D5; 
WidgetLED led1(V2);


BLYNK_WRITE(V2) {
  int value = param.asInt(); // Get value as integer
  if (value == 1) {
    // Then do something to turn ON something

    digitalWrite(LED, LOW);  // Enable digital pin 2
delay(5000);
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V2,0);
    
  } else {
    // Do something to turn OFF something
    digitalWrite(LED, HIGH); // Disable digital pin 2
  }
}


void setup()
{
  Serial.begin(115200);
  delay(100);
Wire.begin();
  BlynkEdgent.begin();

   while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  // bme.chipID(); // Deprecated. See chipModel().
  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }

}

void loop() {
  BlynkEdgent.run();
   printBME280Data(&Serial);
   delay(5000);
timer.run();
}

void printBME280Data
(
   Stream* client
)
{
   float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Fahrenheit);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

   client->print("Temp: ");
   client->print(temp);
   client->print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   client->print("\t\tHumidity: ");
   client->print(hum);
   client->print("% RH");
   client->print("\t\tPressure: ");
   client->print(pres);
   client->println(" Pa");
 Serial.println("Sending Sensor Values to Blynk..." );
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, hum);
   

   delay(10000);
}
