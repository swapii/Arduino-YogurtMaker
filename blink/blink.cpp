#include <Arduino.h>

void setup(void) {
  pinMode(13, OUTPUT);
}

void loop(void) {
  digitalWrite(13, HIGH);
  delay(3000);
  digitalWrite(13, LOW);
  delay(3000);
}
