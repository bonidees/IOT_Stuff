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

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <BME280I2C.h>
#include <Wire.h>

#define SERIAL_BAUD 115200

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Capt. Benson";
char pass[] = "Dick Wolf";

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

//////////////////////////////////////////////////////////////////

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


void setup()
{
  Serial.begin(SERIAL_BAUD);

  while(!Serial) {} // Wait

  Wire.begin();
  Blynk.begin(auth, ssid, pass);
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

//////////////////////////////////////////////////////////////////
void loop()
{
   printBME280Data(&Serial);
   delay(5000);
   Blynk.run();
timer.run();
}

//////////////////////////////////////////////////////////////////
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
