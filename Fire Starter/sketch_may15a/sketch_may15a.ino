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

// V1 LED Widget is blinking
void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
    digitalWrite(LED, LOW);
  } else {
    led1.on();
    Serial.println("LED on V1: on");
    digitalWrite(LED, HIGH);
  }
}

void setup()
{
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(10000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}
