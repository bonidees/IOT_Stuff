
int button = 22;

boolean LED1State = false;
boolean LED2State = false;

long buttonTimer = 0;
long longPressTime = 250;

boolean buttonActive = false;
boolean longPressActive = false;

int ButtonRead = 0;

void setup() {
  pinMode(button, INPUT);
 Serial.begin(115200);
}

void loop() {


  if (digitalRead(button) == HIGH) {

    if (buttonActive == false) {

      buttonActive = true;
      buttonTimer = millis();

    }

    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {

      longPressActive = true;
      ButtonRead = 0;
      Serial.print(ButtonRead);

    }

  } else {

    if (buttonActive == true) {

      if (longPressActive == true) {

        longPressActive = false;

      } else {

        ButtonRead = 0;
      Serial.print(ButtonRead);

      }

      buttonActive = false;

    }

  }

}
