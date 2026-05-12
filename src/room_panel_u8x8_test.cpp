#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <U8x8lib.h>

constexpr uint8_t DHT_PIN = 2;
constexpr uint8_t DHT_TYPE = DHT22;
constexpr uint8_t PIR_PIN = 3;
constexpr uint8_t LDR_DO_PIN = 4;
constexpr uint8_t STATUS_LED_PIN = 8;
constexpr uint8_t BUZZER_PIN = 9;

DHT dht(DHT_PIN, DHT_TYPE);
U8X8_SH1106_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

unsigned long startedAt = 0;
unsigned long lastReadAt = 0;
unsigned long lastBuzzerAt = 0;

bool isPirReady() {
  return millis() - startedAt >= 30000;
}

void setup() {
  startedAt = millis();

  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_DO_PIN, INPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(STATUS_LED_PIN, LOW);
  noTone(BUZZER_PIN);

  Serial.begin(9600);
  delay(500);
  Serial.println(F("Mini Oda Paneli U8x8 basladi."));

  dht.begin();

  display.begin();
  display.setFont(u8x8_font_chroma48medium8_r);
  display.clear();
  display.setCursor(0, 0);
  display.print(F("Mini Oda Paneli"));
  display.setCursor(0, 2);
  display.print(F("DHT hazir..."));
  delay(2500);
}

void loop() {
  const unsigned long now = millis();
  if (now - lastReadAt < 2000 && lastReadAt != 0) {
    return;
  }
  lastReadAt = now;

  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();
  const bool dhtOk = !isnan(humidity) && !isnan(temperatureC);
  const bool isDark = digitalRead(LDR_DO_PIN) == HIGH;
  const bool pirReady = isPirReady();
  const bool motion = pirReady && digitalRead(PIR_PIN) == HIGH;
  const bool alertActive = isDark || motion;

  digitalWrite(STATUS_LED_PIN, alertActive ? HIGH : LOW);
  if (alertActive && now - lastBuzzerAt >= 3000) {
    tone(BUZZER_PIN, 1900, 120);
    lastBuzzerAt = now;
  }

  char tempText[12];
  char humidityText[12];
  if (dhtOk) {
    dtostrf(temperatureC, 4, 1, tempText);
    dtostrf(humidity, 4, 1, humidityText);
  } else {
    strcpy(tempText, "hata");
    strcpy(humidityText, "hata");
  }

  display.clear();
  display.setCursor(0, 0);
  display.print(F("Mini Oda Paneli"));
  display.setCursor(0, 2);
  display.print(F("Sicaklik: "));
  display.print(tempText);
  if (dhtOk) {
    display.print(F(" C"));
  }
  display.setCursor(0, 3);
  display.print(F("Nem:      "));
  display.print(humidityText);
  if (dhtOk) {
    display.print(F(" %"));
  }
  display.setCursor(0, 5);
  display.print(F("Isik: "));
  display.print(isDark ? F("KARANLIK") : F("AYDINLIK"));
  display.setCursor(0, 6);
  display.print(F("Hareket: "));
  if (!pirReady) {
    display.print(F("BEKLE"));
  } else {
    display.print(motion ? F("VAR") : F("YOK"));
  }
  display.setCursor(0, 7);
  display.print(alertActive ? F("LED+BUZZER") : F("Durum normal"));

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
  Serial.print(isDark ? F("karanlik") : F("aydinlik"));
  Serial.print(F(" | Hareket: "));
  if (!pirReady) {
    Serial.println(F("isiniyor"));
  } else {
    Serial.println(motion ? F("var") : F("yok"));
  }
}
