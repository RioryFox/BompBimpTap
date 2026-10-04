#include <Arduin.h>

void setup() {
  Serial.begin(9600); // Initialize UART at 9600 baud rate
}

void loop() {
  Serial.println("UART says Hi!"); // Send message
  delay(1000); // Wait for 1 second
}
