#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <U8x8lib.h>

namespace {
constexpr uint8_t DHT_PIN = 2;
constexpr uint8_t DHT_TYPE = DHT22;
constexpr uint8_t PIR_PIN = 3;
constexpr uint8_t LDR_DO_PIN = 4;
constexpr uint8_t BUTTON_PIN = 5;
constexpr uint8_t HC_SR04_TRIG_PIN = 6;
constexpr uint8_t HC_SR04_ECHO_PIN = 7;
constexpr uint8_t STATUS_LED_PIN = 8;
constexpr uint8_t BUZZER_PIN = 9;

constexpr unsigned long SENSOR_INTERVAL_MS = 2000;
constexpr unsigned long PIR_WARMUP_MS = 30000;
constexpr unsigned long MOTION_BUZZER_INTERVAL_MS = 6000;
constexpr unsigned long BUTTON_IGNORE_MS = 200;
constexpr int NEAR_DISTANCE_CM = 30;
constexpr float TEMP_HIGH_C = 28.0;
constexpr float TEMP_LOW_C = 18.0;

enum TempZone : uint8_t { TEMP_NORMAL, TEMP_HOT, TEMP_COLD };

DHT dht(DHT_PIN, DHT_TYPE);
U8X8_SH1106_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

unsigned long startedAt = 0;
unsigned long lastReadAt = 0;
unsigned long lastBuzzerAt = 0;
unsigned long buttonIgnoreUntil = 0;

bool silentMode = false;
bool buttonArmed = true;
TempZone lastTempZone = TEMP_NORMAL;

// Sensör son değerleri — buzzer her loop'ta bunları kullanır
int lastDistanceCm = -1;
bool lastNearObject = false;
bool lastMotion = false;
bool lastIsDark = false;
TempZone lastTempZoneForBuzzer = TEMP_NORMAL;

bool isPirReady() {
  return millis() - startedAt >= PIR_WARMUP_MS;
}

// Sol→La→Si, Sol→La→Si (yükselen — sıcak alarm)
void playHighTempAlarm() {
  tone(BUZZER_PIN, 392, 150); delay(180);
  tone(BUZZER_PIN, 440, 150); delay(180);
  tone(BUZZER_PIN, 494, 200); delay(350);
  tone(BUZZER_PIN, 392, 150); delay(180);
  tone(BUZZER_PIN, 440, 150); delay(180);
  tone(BUZZER_PIN, 494, 200); delay(200);
}

// Si→La→Sol, Si→La→Sol (inen — soğuk alarm)
void playLowTempAlarm() {
  tone(BUZZER_PIN, 494, 150); delay(180);
  tone(BUZZER_PIN, 440, 150); delay(180);
  tone(BUZZER_PIN, 392, 200); delay(350);
  tone(BUZZER_PIN, 494, 150); delay(180);
  tone(BUZZER_PIN, 440, 150); delay(180);
  tone(BUZZER_PIN, 392, 200); delay(200);
}

// Mesafe bölgesine göre buzzer aralığı
unsigned long distanceBuzzerInterval(int distanceCm) {
  if (distanceCm > 0 && distanceCm <= 10) return 25;
  if (distanceCm > 10 && distanceCm <= 20) return 100;
  if (distanceCm > 20 && distanceCm <= NEAR_DISTANCE_CM) return 250;
  return 0;
}

// Mesafe bölgesine göre bip sesi
void beepForDistance(int distanceCm) {
  if (distanceCm <= 10) {
    tone(BUZZER_PIN, 1800, 40);
  } else if (distanceCm <= 20) {
    tone(BUZZER_PIN, 1400, 80);
  } else {
    tone(BUZZER_PIN, 1000, 120);
  }
}

void drawSilentModeFeedback() {
  display.clear();
  display.setCursor(0, 0);
  display.print(F("Buton algilandi"));
  display.setCursor(0, 2);
  display.print(F("Sessiz mod:"));
  display.setCursor(0, 4);
  display.print(silentMode ? F("ACIK") : F("KAPALI"));
}

void drawBootScreen() {
  display.clear();
  display.setCursor(0, 0);
  display.print(F("Mini Oda Paneli"));
  display.setCursor(0, 2);
  display.print(F("V2 basliyor..."));
  display.setCursor(0, 4);
  display.print(F("PIR isinma 30s"));
}

int readDistanceCm() {
  digitalWrite(HC_SR04_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(HC_SR04_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_SR04_TRIG_PIN, LOW);

  const unsigned long duration = pulseIn(HC_SR04_ECHO_PIN, HIGH, 25000);
  if (duration == 0) return -1;
  return static_cast<int>(duration / 58);
}

void updateButton() {
  const unsigned long now = millis();
  if (now < buttonIgnoreUntil) return;

  const bool raw = digitalRead(BUTTON_PIN) == LOW;
  if (!raw) {
    buttonArmed = true;
    return;
  }
  if (!buttonArmed) return;

  buttonArmed = false;
  buttonIgnoreUntil = now + BUTTON_IGNORE_MS;

  silentMode = !silentMode;
  Serial.print(F("Sessiz mod: "));
  Serial.println(silentMode ? F("ACIK") : F("KAPALI"));
  drawSilentModeFeedback();
  lastReadAt = 0;
}

void drawPanel(float temperatureC, float humidity, bool dhtOk, bool isDark,
               bool pirReady, bool motion, int distanceCm, bool nearObject,
               TempZone tempZone) {
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
  if (dhtOk) display.print(F(" C"));

  display.setCursor(0, 3);
  display.print(F("Nem:      "));
  display.print(humidityText);
  if (dhtOk) display.print(F(" %"));

  display.setCursor(0, 5);
  display.print(F("Isik: "));
  display.print(isDark ? F("KARANLIK") : F("AYDINLIK"));

  display.setCursor(0, 6);
  display.print(F("Har:"));
  if (!pirReady) {
    display.print(F("BEKLE"));
  } else {
    display.print(motion ? F("VAR") : F("YOK"));
  }
  display.print(F(" M:"));
  if (distanceCm < 0) {
    display.print(F("--"));
  } else {
    display.print(distanceCm);
    display.print(F("cm"));
  }

  display.setCursor(0, 7);
  if (silentMode) {
    display.print(F("Sessiz mod"));
  } else if (tempZone == TEMP_HOT) {
    display.print(F("COK SICAK!"));
  } else if (tempZone == TEMP_COLD) {
    display.print(F("COK SOGUK!"));
  } else if (isDark) {
    display.print(F("LED aktif"));
  } else if (nearObject) {
    display.print(F("Yakin nesne!"));
  } else if (motion) {
    display.print(F("Hareket var!"));
  } else {
    display.print(F("Durum normal"));
  }
}

void printSerialStatus(float temperatureC, float humidity, bool dhtOk, bool isDark,
                       bool pirReady, bool motion, int distanceCm, bool nearObject,
                       TempZone tempZone) {
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
    Serial.print(F("isiniyor"));
  } else {
    Serial.print(motion ? F("var") : F("yok"));
  }
  Serial.print(F(" | Mesafe: "));
  if (distanceCm < 0) {
    Serial.print(F("yok"));
  } else {
    Serial.print(distanceCm);
    Serial.print(F(" cm"));
  }
  Serial.print(F(" | Yakin: "));
  Serial.print(nearObject ? F("evet") : F("hayir"));
  Serial.print(F(" | Sicaklik alarm: "));
  if (tempZone == TEMP_HOT) Serial.print(F("COK SICAK"));
  else if (tempZone == TEMP_COLD) Serial.print(F("COK SOGUK"));
  else Serial.print(F("normal"));
  Serial.print(F(" | Sessiz: "));
  Serial.println(silentMode ? F("acik") : F("kapali"));
}
}  // namespace

void setup() {
  startedAt = millis();

  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_DO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(HC_SR04_TRIG_PIN, OUTPUT);
  pinMode(HC_SR04_ECHO_PIN, INPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(HC_SR04_TRIG_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);
  noTone(BUZZER_PIN);

  Serial.begin(9600);
  delay(500);
  Serial.println(F("Mini Akilli Oda Kontrol Paneli V2"));
  Serial.println(F("DHT22 D2 | PIR D3 | LDR D4 | Button D5 | HC-SR04 D6/D7 | LED D8 | Buzzer D9"));

  dht.begin();

  display.begin();
  display.setFont(u8x8_font_chroma48medium8_r);
  drawBootScreen();
  delay(2500);
}

void loop() {
  updateButton();

  const unsigned long now = millis();

  // Buzzer her loop'ta kontrol edilir — sensör aralığına bağlı değil
  if (!silentMode) {
    const unsigned long interval = distanceBuzzerInterval(lastDistanceCm);
    if (interval > 0 && now - lastBuzzerAt >= interval) {
      beepForDistance(lastDistanceCm);
      lastBuzzerAt = now;
    } else if (interval == 0 && lastMotion && now - lastBuzzerAt >= MOTION_BUZZER_INTERVAL_MS) {
      tone(BUZZER_PIN, 1200, 35);
      lastBuzzerAt = now;
    }
  }

  // Sensör okuması 2 saniyede bir
  if (now - lastReadAt < SENSOR_INTERVAL_MS && lastReadAt != 0) return;
  lastReadAt = now;

  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();
  const bool dhtOk = !isnan(humidity) && !isnan(temperatureC);
  const bool isDark = digitalRead(LDR_DO_PIN) == HIGH;
  const bool pirReady = isPirReady();
  const bool motion = pirReady && digitalRead(PIR_PIN) == HIGH;
  const int distanceCm = readDistanceCm();
  const bool nearObject = distanceCm > 0 && distanceCm <= NEAR_DISTANCE_CM;

  // Kalıcı değerleri güncelle
  lastDistanceCm = distanceCm;
  lastNearObject = nearObject;
  lastMotion = motion;
  lastIsDark = isDark;

  // Sıcaklık alarmı — zone değişince melodi çal
  TempZone tempZone = TEMP_NORMAL;
  if (dhtOk) {
    if (temperatureC > TEMP_HIGH_C) tempZone = TEMP_HOT;
    else if (temperatureC < TEMP_LOW_C) tempZone = TEMP_COLD;

    if (tempZone != lastTempZone) {
      lastTempZone = tempZone;
      lastTempZoneForBuzzer = tempZone;
      if (!silentMode) {
        if (tempZone == TEMP_HOT) playHighTempAlarm();
        else if (tempZone == TEMP_COLD) playLowTempAlarm();
      }
    }
  }

  // LED
  digitalWrite(STATUS_LED_PIN, (isDark || nearObject) ? HIGH : LOW);

  drawPanel(temperatureC, humidity, dhtOk, isDark, pirReady, motion, distanceCm, nearObject, tempZone);
  printSerialStatus(temperatureC, humidity, dhtOk, isDark, pirReady, motion, distanceCm, nearObject, tempZone);
}
