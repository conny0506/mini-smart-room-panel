#include <Arduino.h>

constexpr uint8_t STATUS_LED_PIN = 8;

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(STATUS_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(STATUS_LED_PIN, LOW);
  delay(1000);
}
