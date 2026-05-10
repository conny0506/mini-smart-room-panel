#include <Arduino.h>

constexpr uint8_t LDR_PIN = A0;
constexpr uint8_t STATUS_LED_PIN = 8;
constexpr int DARK_THRESHOLD = 350;

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  Serial.begin(9600);
  delay(500);
  Serial.println(F("LDR test basladi."));
  Serial.println(F("A0 degeri aydinlikta ve karanlikta degismeli."));
}

void loop() {
  const int lightValue = analogRead(LDR_PIN);
  const bool isDark = lightValue < DARK_THRESHOLD;

  digitalWrite(STATUS_LED_PIN, isDark ? HIGH : LOW);

  Serial.print(F("LDR A0: "));
  Serial.print(lightValue);
  Serial.println(isDark ? F(" -> karanlik") : F(" -> aydinlik"));

  delay(500);
}
