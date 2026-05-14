#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 5;
constexpr uint8_t LED_PIN = 8;
constexpr uint8_t BUZZER_PIN = 9;
constexpr unsigned long BUTTON_IGNORE_MS = 200;
constexpr unsigned long RAW_PRINT_INTERVAL_MS = 300;

unsigned long buttonIgnoreUntil = 0;
bool buttonArmed = true;

bool silentMode = false;
int pressCount = 0;

unsigned long lastRawPrintAt = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  Serial.begin(9600);
  delay(500);

  Serial.println(F("=== KY-004 Baglanti Testi ==="));
  Serial.println(F("Baglanti: S -> D5  |  orta -> 5V  |  - -> GND"));
  Serial.println(F("Hizlica bas-birak yeterli, tutmak gerekmez."));
  Serial.println(F("-----------------------------"));
}

void loop() {
  const unsigned long now = millis();

  // Periyodik ham durum — bağlantı doğrulaması
  if (now - lastRawPrintAt >= RAW_PRINT_INTERVAL_MS) {
    lastRawPrintAt = now;
    const bool rawNow = digitalRead(BUTTON_PIN) == LOW;
    Serial.print(F("Ham: "));
    Serial.print(rawNow ? F("HIGH") : F("LOW "));
    Serial.print(F("  Sessiz: "));
    Serial.println(silentMode ? F("ACIK  ") : F("KAPALI"));
  }

  // İgnore penceresi aktifse hiçbir şey yapma
  if (now < buttonIgnoreUntil) {
    return;
  }

  const bool raw = digitalRead(BUTTON_PIN) == LOW;

  if (!raw) {
    buttonArmed = true;
    return;
  }

  if (!buttonArmed) {
    return;
  }

  // İlk HIGH algılandı → anında kayıt
  buttonArmed = false;
  buttonIgnoreUntil = now + BUTTON_IGNORE_MS;

  pressCount++;
  silentMode = !silentMode;

  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 2000, 80);
  delay(80);
  digitalWrite(LED_PIN, LOW);

  Serial.println(F("-----------------------------"));
  Serial.print(F("BASIM #"));
  Serial.println(pressCount);
  Serial.print(F("Sessiz mod: "));
  Serial.println(silentMode ? F("ACIK") : F("KAPALI"));
  Serial.println(F("-----------------------------"));
}
