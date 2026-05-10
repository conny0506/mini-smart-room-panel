#include <Arduino.h>

constexpr uint8_t BUZZER_PIN = 9;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  tone(BUZZER_PIN, 1800, 150);
  delay(500);
  tone(BUZZER_PIN, 2200, 150);
  delay(1000);
}
