#include <Arduino.h>

constexpr uint8_t LDR_DO_PIN = 4;
constexpr uint8_t STATUS_LED_PIN = 8;

void setup() {
  pinMode(LDR_DO_PIN, INPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);

  Serial.begin(9600);
  delay(500);
  Serial.println(F("LDR modul testi basladi."));
  Serial.println(F("VCC -> 5V, GND -> GND, DO -> D4"));
}

void loop() {
  const int digitalValue = digitalRead(LDR_DO_PIN);

  digitalWrite(STATUS_LED_PIN, digitalValue == HIGH ? HIGH : LOW);

  Serial.print(F("LDR DO: "));
  Serial.println(digitalValue == HIGH ? F("HIGH") : F("LOW"));

  delay(500);
}
