#include <Arduino.h>
#define LED_PIN PG7

extern "C" void SystemClock_Config(void) {
  SystemCoreClockUpdate();
};

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
