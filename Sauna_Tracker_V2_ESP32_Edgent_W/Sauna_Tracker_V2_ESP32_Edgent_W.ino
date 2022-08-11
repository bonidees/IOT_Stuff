
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLJmpAUome"
#define BLYNK_DEVICE_NAME "Fire Starter"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define pin_SDA                         D2
#define pin_SCL                         D1
#define BME280_I2C_ADDRESS 0x76



// constants won't change. They're used here to set pin numbers for the button:
const int buttonPin = D4;    // the number of the pushbutton pin
const int ledPin = D8;      // the number of the LED pin
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
//int lampamasa;
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers




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
//float l = lampamasa();

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
  Serial.println("Lampamasa: ");
 // Serial.print(l);

 Serial.println("Sending Sensor Values to Blynk..." );
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
Blynk.virtualWrite(V2, ledState);



//TO DO 5
  
 // Blynk.syncVirtual(V0,V1);
  //Serial.println(V0);
 // Serial.println(V1);
   

}

void setup()
{
  Serial.begin(115200);
//button stuff
    pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
//lampamasa == 0;
    digitalWrite(ledPin, ledState);
// end button stuff

  delay(20);

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
  int reading = digitalRead(buttonPin);

    // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
    if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        Serial.print("lampamasa on ");
//        lampamasa == 1;
      }   else  
    //    lampamasa == 0;
      Serial.print("lampamasa off ");
    }
  }
    digitalWrite(ledPin, ledState);
      lastButtonState = reading;
  //end button stuff
   if(Blynk.connected()){
 delay(50);
 
 Blynk.run();
 timer.run();
 } else  Serial.print("Trying to connect again... ");



}
