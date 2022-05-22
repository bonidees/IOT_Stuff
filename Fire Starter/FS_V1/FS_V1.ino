/*************************************************************

  Blynk using a LED widget on your phone!

  App project setup:
    LED widget on V1
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLJmpAUome"
#define BLYNK_DEVICE_NAME "Fire Starter V1"
#define BLYNK_AUTH_TOKEN "l-H3RAHApa61uX4pPc1o5HXpnAiuqHrn"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
//#define pin_SDA                         D2
//#define pin_SCL                         D1
#define BME280_I2C_ADDRESS 0x76

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "SparkFunBME280.h"
#include "wire.h"


BME280 BME280_sensor;


char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Capt. Benson";
char pass[] = "Dick Wolf";


int LED = D5; 
WidgetLED led1(V2);

BlynkTimer timer;

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

void sendSensor()
{
 // float h = dht.readHumidity();
  float t = BME280_sensor.readTempF(); 
  float h = BME280_sensor.readFloatHumidity();
  // You can send any value at any time.
  // Please don't send more than 10 values per second.
  Serial.println("Temp:" );
  Serial.print(t);
  Serial.println("Humidity: ");
  Serial.print(h);
 Serial.println("Sending Sensor Values to Blynk..." );
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
  

void setup()
{
pinMode(LED, OUTPUT);
digitalWrite(LED, HIGH);
  // Debug console
  Serial.begin(115200);
  // BlynkEdgent.begin();
 // Wire.setPins(pin_SDA, pin_SCL);
//Wire.begin();
// init BME280
BME280_sensor.setI2CAddress(BME280_I2C_ADDRESS);
BME280_sensor.beginI2C();

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every 200 seconds
timer.setInterval(10000L, sendSensor);
}

void loop()
{
Blynk.run();
timer.run();
}
