#include <Arduino.h>
#define LED_PIN PG7

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("Bomp!");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  Serial.println("Bimp!");
  delay(1000);
}
