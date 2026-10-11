#include <Arduino.h>
#define LED_PIN PG7

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
}
