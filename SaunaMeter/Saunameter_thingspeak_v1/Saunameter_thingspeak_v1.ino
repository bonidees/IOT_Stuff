/*
  WriteMultipleFields
  
  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.
  
  Hardware: ESP8266 based boards
  
  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
  Note:
  - Requires ESP8266WiFi library and ESP8622 board add-on. See https://github.com/esp8266/Arduino for details.
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.  
  
  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.
  
  For licensing information, see the accompanying license file.
  
  Copyright 2020, The MathWorks, Inc.
*/

#include <ESP8266WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;


#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
          
// Initialize our values
int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);
String myStatus = "";

float HUMIDITY;
float TEMPERATURE_C;
float TEMPERATURE_F;
float temp(NAN), hum(NAN), pres(NAN);


// Global variables.
int numMeasure = 3;                                // Number of measurements to average.
int ADCValue = 0;                                  // Moisture sensor reading.

void setup() {
  Serial.begin(115200);  // Initialize serial
  Wire.begin();
bme.begin(0x76);


  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  

HUMIDITY = readHumidity(numMeasure);
Serial.print("Humidity = ");
Serial.println(HUMIDITY);

TEMPERATURE_C = readTempC(numMeasure);
Serial.print("Temperature C = ");
Serial.println(TEMPERATURE_C);

TEMPERATURE_F = readTempF(numMeasure);
Serial.print("Temperature F = ");
Serial.println(TEMPERATURE_F);

Serial.print("Barometric Pressure = ");

ThingSpeak.setField(1, HUMIDITY);
ThingSpeak.setField(2, TEMPERATURE_C);
ThingSpeak.setField(3, TEMPERATURE_F);
//ThingSpeak.setField(4, WHATEVER);
//ThingSpeak.setField(5, WHATEVER);
//ThingSpeak.setField(6, WHATEVER);
//ThingSpeak.setField(8, WHATEVER);
ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);


   
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(40000); // Wait 20 seconds to update the channel again
}

long readHumidity(int numAve) {
long h = 0;

for ( int i = 0; i < numAve; i++ ) {

h += bme.readHumidity();   // Read the value from sensor
}
h = h / numAve;
return h;                    // Return the humidity value.
}



long readTempC(int numAve) {
long tempC = 0;

for ( int i = 0; i < numAve; i++ ) {

tempC += bme.readTemperature();      // Read the value from sensor
}
tempC = tempC / numAve;
return tempC;                    // Return the tempC value.
}





//dothis
long readTempF(int numAve) {
long tempF = 0;

for ( int i = 0; i < numAve; i++ ) {
tempF += bme.readTemperature();     // Read the value from sensor
}
tempF = ((tempF / numAve)* 9 / 5 + 32);
return tempF;                    // Return the tempF value.
}
