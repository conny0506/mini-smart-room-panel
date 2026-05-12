#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

constexpr uint8_t DHT_PIN = 2;
constexpr uint8_t LDR_DO_PIN = 4;
constexpr uint8_t STATUS_LED_PIN = 8;
constexpr uint8_t BUZZER_PIN = 9;

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_RESET_PIN = -1;
constexpr uint8_t OLED_ADDRESS = 0x3C;

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

unsigned long lastReadAt = 0;
unsigned long lastBuzzerAt = 0;
float temperatureC = NAN;
float humidity = NAN;
bool dhtOk = false;
bool isDark = false;

bool readDHT22(float &temperatureOut, float &humidityOut) {
  uint8_t data[5] = {0, 0, 0, 0, 0};

  pinMode(DHT_PIN, INPUT_PULLUP);
  delay(1);

  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, LOW);
  delayMicroseconds(1100);

  pinMode(DHT_PIN, INPUT_PULLUP);
  delayMicroseconds(55);

  const unsigned long responseLow = pulseIn(DHT_PIN, LOW, 2000);
  const unsigned long responseHigh = pulseIn(DHT_PIN, HIGH, 2000);
  if (responseLow == 0 || responseHigh == 0) {
    return false;
  }

  for (uint8_t i = 0; i < 40; i++) {
    const unsigned long lowPulse = pulseIn(DHT_PIN, LOW, 2000);
    const unsigned long highPulse = pulseIn(DHT_PIN, HIGH, 2000);
    if (lowPulse == 0 || highPulse == 0) {
      return false;
    }

    data[i / 8] <<= 1;
    if (highPulse > lowPulse) {
      data[i / 8] |= 1;
    }
  }

  const uint8_t checksum = (data[0] + data[1] + data[2] + data[3]) & 0xFF;
  if (data[4] != checksum) {
    return false;
  }

  const uint16_t rawHumidity = (static_cast<uint16_t>(data[0]) << 8) | data[1];
  uint16_t rawTemperature = (static_cast<uint16_t>(data[2]) << 8) | data[3];

  const bool negative = (rawTemperature & 0x8000) != 0;
  rawTemperature &= 0x7FFF;

  humidityOut = rawHumidity / 10.0;
  temperatureOut = rawTemperature / 10.0;
  if (negative) {
    temperatureOut = -temperatureOut;
  }

  return true;
}

void drawScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.println(F("Mini Oda Paneli"));
  display.println(F("----------------"));

  display.print(F("Sicaklik: "));
  if (dhtOk) {
    display.print(temperatureC, 1);
    display.println(F(" C"));
  } else {
    display.println(F("DHT hata"));
  }

  display.print(F("Nem:      "));
  if (dhtOk) {
    display.print(humidity, 1);
    display.println(F(" %"));
  } else {
    display.println(F("--"));
  }

  display.print(F("Isik:     "));
  display.println(isDark ? F("KARANLIK") : F("AYDINLIK"));

  display.println();
  display.println(isDark ? F("LED/BUZZER AKTIF") : F("Durum normal"));

  display.display();
}

void setup() {
  pinMode(LDR_DO_PIN, INPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(STATUS_LED_PIN, LOW);
  noTone(BUZZER_PIN);

  Serial.begin(9600);
  delay(500);
  Serial.println(F("Mini Oda Paneli test basladi."));
  Serial.println(F("DHT22: D2 | LDR DO: D4 | LED: D8 | Buzzer: D9"));

  pinMode(DHT_PIN, INPUT_PULLUP);
  Wire.begin();

  Serial.println(F("OLED baslatiliyor..."));
  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println(F("OLED baslatilamadi."));
    while (true) {
      digitalWrite(STATUS_LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000, 80);
      delay(400);
      digitalWrite(STATUS_LED_PIN, LOW);
      delay(400);
    }
  }
  Serial.println(F("OLED baslatildi."));

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println(F("Mini Oda Paneli"));
  display.println(F("DHT hazirlaniyor..."));
  display.display();
  delay(4000);
  Serial.println(F("Loop basliyor."));
}

void loop() {
  const unsigned long now = millis();

  if (now - lastReadAt >= 2000 || lastReadAt == 0) {
    lastReadAt = now;

    Serial.println(F("DHT okunuyor..."));
    float newTemperatureC = NAN;
    float newHumidity = NAN;
    dhtOk = readDHT22(newTemperatureC, newHumidity);
    if (dhtOk) {
      humidity = newHumidity;
      temperatureC = newTemperatureC;
    }

    isDark = digitalRead(LDR_DO_PIN) == HIGH;
    digitalWrite(STATUS_LED_PIN, isDark ? HIGH : LOW);

    if (isDark && now - lastBuzzerAt >= 3000) {
      tone(BUZZER_PIN, 1900, 120);
      lastBuzzerAt = now;
    }

    Serial.print(F("Sicaklik: "));
    if (dhtOk) {
      Serial.print(temperatureC, 1);
      Serial.print(F(" C | Nem: "));
      Serial.print(humidity, 1);
      Serial.print(F(" %"));
    } else {
      Serial.print(F("DHT hata"));
    }
    Serial.print(F(" | Isik: "));
    Serial.println(isDark ? F("karanlik") : F("aydinlik"));

    drawScreen();
  }
}
