/*********
  Rui Santos
  https://randomnerdtutorials.com/esp32-esp8266-i2c-lcd-arduino-ide/
  LIB USED: LiquidCrystal_I2C We’re using this library by 'Marco Schwartz'.

USED: "DOIT ESP32 DEVKIT V1 CHIP".
   
*********/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include Adafruit_Sensor.h
#include Adafruit_BME280.h



// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

#define SEALEVELPRESSURE_HPA (1013.25)

 Adafruit_BME280 bme; // I2C

//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;
#define key_1 13   // The two buttons on P13, P14
#define key_2 14 
void printValues();
void printTemp();
void printHum();

void setup(){

 pinMode(key_1,INPUT_PULLUP);
 pinMode(key_2,INPUT_PULLUP); 

 
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
Wire.begin(39, 42);
   Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
                        // You can also pass in a Wire library object like &Wire2 SURE.
   status = bme.begin(0x76); 
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}

void loop(){
  bool sw1= digitalRead(key_1);
  if (sw1 ==0)
   printTemp();
   
  bool sw2= digitalRead(key_2);
   if (sw2== 0)
   printHum();
  
  
    // set cursor to first column, first row
  printValues();
    delay(delayTime);
  
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Nicholas Upton. ");
 
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Sauna World ");
  delay(3000);
  lcd.clear(); 

  
}

void printTemp()
{
  lcd.clear();
   delay(delayTime);
 
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Temp: ");
 
  lcd.setCursor(8, 0);  // right 8 places on first line.
  lcd.print(bme.readTemperature());
  delay(3000); // SHOW IT FOR 3 SECONDS AND RETURN TO MAIN SCREEN.
  lcd.clear();
}
void printHum()
{
  lcd.clear(); 
   delay(delayTime);
  //delay(1500);
  lcd.setCursor(0, 1);
  // print message
  lcd.print("Humidity% = ");
 
  lcd.setCursor(12, 1);  // right 8 places on first line.
  lcd.print(bme.readHumidity());
  delay(3000);  // SHOW IT FOR 3 SECONDS AND RETURN TO MAIN SCREEN.
  lcd.clear();
 
}

void printValues() {              // DISPLAY ASLL ON SERIAL MONITOR.
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}
