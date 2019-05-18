#include "Arduino.h"
#include "SonicDistance.h"

const int TOGGLE_PIN = 13;
const int TRIG_PIN = 9;
const int ECHO_PIN = 9;
const int PWM_LED = 10;
const unsigned int min_limit = 50;
const unsigned int max_limit = 1000;
int distance;
int brightness;
boolean toggle;
SonicDistance sonicDistance(TRIG_PIN, ECHO_PIN, min_limit, max_limit);

void setup()
{
  pinMode(PWM_LED, OUTPUT);
  pinMode(TOGGLE_PIN, OUTPUT);
  toggle = true;
}

void loop()
{
  distance = sonicDistance.getFilteredDistance() / 1000;
  brightness = map(distance, max_limit, min_limit, 0, 255);
  analogWrite(PWM_LED, brightness);
  if (toggle)
  {
    digitalWrite(TOGGLE_PIN, HIGH);
    toggle = false;
  }
  else
  {
    digitalWrite(TOGGLE_PIN, LOW);
    toggle = true;
  }
  delay(20);
}
