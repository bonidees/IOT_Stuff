
/*
* What is this shit? 
* 
* This is a temperature, humidity and barometric pressure sensor designed for easy connection to
* Thingspeak, the IOT platform within Matlab. 
* 
* What you need: 
* All inputs are marked as "XXXXX." You'll need a free Thingspeak account. Then a channel. You'll need to input the channel, write and read API codes for this to work. 
* 
* Wifi credentials (duh) 
* 
* An Arduino usable ESP 8266 like the Wemos D1 mini or whatever. 
* 
* BME 280 breakout sensor.
* 
* How it works:
* 
* Connects to Wifi
* Reads the sensor
* sends the readings to Thingspeak
* goes to sleep 
* 
*/

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "ThingSpeak.h"
#include <BME280I2C.h>






//Temp-Humidity-Pressure sensor
BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
          // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,


// Network information.
#define WIFI_NAME "XXXXX"
#define PASSWORD "XXXXX"



// Hardware information.
#define TIMEOUT  5000                              // Timeout for server response.
#define SLEEP_TIME_SECONDS 300

// ThingSpeak information.
float HUMIDITY;
float TEMPERATURE_C;
float TEMPERATURE_F;
float BAROMETRICp;
float temp(NAN), hum(NAN), pres(NAN);
#define THING_SPEAK_ADDRESS "api.thingspeak.com"
const char * myWriteAPIKey = "Y0UZ835AYR37QSWF";           // Change this to your channel Write API key.
const char * myReadAPIKey = "9NEI79I3X5SKD72C";
unsigned long myChannel = 2083964;

#define pump D8


// Global variables.
int numMeasure = 3;                                // Number of measurements to average.
int ADCValue = 0;                                  // Moisture sensor reading.

WiFiClient client;

// Put your setup code here, to run once:
void setup()
{
Serial.begin( 9600 );   // You may need to adjust the speed depending on your hardware.
Wire.begin();
bme.begin();
while(!bme.begin())
{
Serial.println("Could not find BME280 sensor!");
delay(1000);
}


connectWifi();
ThingSpeak.begin(client);
pinMode(pump, OUTPUT);
//pinMode(pump2, OUTPUT);
digitalWrite(pump, LOW); //turn off the pump
//  digitalWrite(pump2, LOW); //turn off the pump


}

// Put your main code here, to run repeatedly:
void loop()
{


BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
BME280::PresUnit presUnit(BME280::PresUnit_Pa);
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

bme.read(pres, temp, hum, tempUnit, presUnit);

HUMIDITY = readHumidity(numMeasure);
Serial.print("Humidity = ");
Serial.println(HUMIDITY);

TEMPERATURE_C = readTempC(numMeasure);
Serial.print("Temperature C = ");
Serial.println(TEMPERATURE_C);

TEMPERATURE_F = readTempF(numMeasure);
Serial.print("Temperature F = ");
Serial.println(TEMPERATURE_F);

BAROMETRICp = readBar(numMeasure);
Serial.print("Barometric Pressure = ");
Serial.println(BAROMETRICp);

ThingSpeak.setField(1, HUMIDITY);
ThingSpeak.setField(2, TEMPERATURE_C);
ThingSpeak.setField(3, TEMPERATURE_F);
//ThingSpeak.setField(4, WHATEVER);
//ThingSpeak.setField(5, WHATEVER);
//ThingSpeak.setField(6, WHATEVER);
ThingSpeak.setField(7, BAROMETRICp);
//ThingSpeak.setField(8, WHATEVER);
ThingSpeak.writeFields(myChannel, myWriteAPIKey);

Serial.println("Function complete, time to rest.");


delay( 200 );
Serial.println( "Goodnight for " + String( SLEEP_TIME_SECONDS ) + " Seconds" );
ESP.deepSleep(300e6);

//delay(40000);

// If you remove the sleep, add delay so you don't post to ThingSpeak too often.

}


long readHumidity(int numAve) {
long h = 0;

for ( int i = 0; i < numAve; i++ ) {

h += hum;   // Read the value from sensor
}
h = h / numAve;
return h;                    // Return the humidity value.
}



long readTempC(int numAve) {
long tempC = 0;

for ( int i = 0; i < numAve; i++ ) {

tempC += temp;      // Read the value from sensor
}
tempC = tempC / numAve;
return tempC;                    // Return the tempC value.
}





//dothis
long readTempF(int numAve) {
long tempF = 0;

for ( int i = 0; i < numAve; i++ ) {
tempF += temp;     // Read the value from sensor
}
tempF = ((tempF / numAve)* 9 / 5 + 32);
return tempF;                    // Return the tempF value.
}


long readBar(int numAve) {
long BarP = 0;
for ( int i = 0; i < numAve; i++ ) {
BarP += pres;      // Read the value from sensor
}
BarP = BarP / numAve;
return BarP;                    // Return the tempC value.
}

// Connect to the local WiFi network
long connectWifi()
{

while (WiFi.status() != WL_CONNECTED) {
WiFi.mode(WIFI_STA);
WiFi.hostname(WIFI_NAME); 
WiFi.begin( WIFI_NAME , PASSWORD );
Serial.println( "Connecting to WiFi" );
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");

}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
Serial.println( "Connected" );  // Inform the serial monitor.
}
