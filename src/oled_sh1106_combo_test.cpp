#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_RESET_PIN = -1;
constexpr uint8_t OLED_ADDRESS = 0x3C;

constexpr uint8_t STATUS_LED_PIN = 8;
constexpr uint8_t BUZZER_PIN = 9;

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
  delay(500);
  Serial.println(F("SH1106 OLED + LED + buzzer testi basladi."));
  Serial.println(F("OLED: GND->GND, VCC->5V, SCK->A5, SDA->A4"));
  Serial.println(F("LED: D8, buzzer: D9"));

  Wire.begin();
  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println(F("OLED baslatilamadi. Kablo veya adres kontrol et."));
    while (true) {
      digitalWrite(STATUS_LED_PIN, HIGH);
      tone(BUZZER_PIN, 1200, 80);
      delay(400);
      digitalWrite(STATUS_LED_PIN, LOW);
      delay(400);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println(F("OLED duzeldi mi?"));
  display.println(F("SH1106 test"));
  display.println();
  display.println(F("LED D8"));
  display.println(F("Buzzer D9"));
  display.display();

  tone(BUZZER_PIN, 1800, 120);
}

void loop() {
  static unsigned long counter = 0;
  const bool ledOn = counter % 2 == 0;

  digitalWrite(STATUS_LED_PIN, ledOn ? HIGH : LOW);
  if (ledOn) {
    tone(BUZZER_PIN, 2000, 80);
  }

  display.fillRect(0, 48, SCREEN_WIDTH, 16, SH110X_BLACK);
  display.setCursor(0, 50);
  display.print(F("Sayac: "));
  display.print(counter);
  display.print(ledOn ? F(" LED ON") : F(" LED OFF"));
  display.display();

  Serial.print(F("Sayac: "));
  Serial.println(counter);

  counter++;
  delay(1000);
}
