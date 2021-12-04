
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLnhptwnXc"
#define BLYNK_DEVICE_NAME "Test FlorA Template"

//added from DHT code
#define BLYNK_PRINT Serial
#define DHTPIN 22          // What digital pin we're connected to


#define BLYNK_FIRMWARE_VERSION        "0.1.2"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7



//added from DHT CODE DO I NEED ETHERNET?
#include <SPI.h>
//#include <Ethernet.h>
//#include <BlynkSimpleEthernet.h>
#include <DHT.h>
#include "BlynkEdgent.h"




// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;



void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(true); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Serial.println("Temp:" );
  Serial.print(t);
  Serial.println("Humidity: ");
  Serial.print(h);
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}



void setup()
{
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();

  //start blynk for dht, then turn on dht
 // Blynk.begin(auth);
  dht.begin();

  // Setup a function to be called every 20 seconds
  timer.setInterval(20000L, sendSensor);

}

void loop() {
  BlynkEdgent.run();

  //turn on blynk for sending sensor data, then time out
  Blynk.run();
  timer.run();
}
