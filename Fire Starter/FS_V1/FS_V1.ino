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

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Capt. Benson";
char pass[] = "Dick Wolf";

int LED = D5; 
WidgetLED led1(V1);

BlynkTimer timer;

BLYNK_WRITE(V1) {
  int value = param.asInt(); // Get value as integer
  if (value == 1) {
    // Then do something to turn ON something

    digitalWrite(LED, LOW);  // Enable digital pin 2
delay(5000);
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V1,0);
    
  } else {
    // Do something to turn OFF something
    digitalWrite(LED, HIGH); // Disable digital pin 2
  }
}

void starter()
{
}
  

void setup()
{
pinMode(LED, OUTPUT);
digitalWrite(LED, HIGH);
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

}

void loop()
{
  Blynk.run();
}
