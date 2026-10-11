#include <Arduino.h>

void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.println("UART says Hi!"); 
  delay(1000);
}
