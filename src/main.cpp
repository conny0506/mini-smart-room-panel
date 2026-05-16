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
constexpr unsigned long LONG_PRESS_MS = 1000;
constexpr int NEAR_DISTANCE_CM = 30;
constexpr float TEMP_HIGH_C = 28.0;
constexpr float TEMP_LOW_C = 18.0;

enum TempZone : uint8_t { TEMP_NORMAL, TEMP_HOT, TEMP_COLD };
enum ButtonState : uint8_t { BTN_IDLE, BTN_DEBOUNCING, BTN_PRESSED };

DHT dht(DHT_PIN, DHT_TYPE);
U8X8_SH1106_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

unsigned long startedAt = 0;
unsigned long lastReadAt = 0;
unsigned long lastBuzzerAt = 0;
unsigned long pressStartAt = 0;

bool silentMode = false;
bool musicMode = false;
bool longPressHandled = false;
ButtonState btnState = BTN_IDLE;
TempZone lastTempZone = TEMP_NORMAL;

// Sensör son değerleri — buzzer her loop'ta bunları kullanır
int lastDistanceCm = -1;
bool lastNearObject = false;
bool lastMotion = false;
bool lastIsDark = false;
TempZone lastTempZoneForBuzzer = TEMP_NORMAL;

// ── Tetris (Korobeiniki) ──────────────────────────────────────
static const uint16_t TETRIS_FREQS[] PROGMEM = {
  659,494,523,587,523,494,  440,440,523,659,587,523,
  494,523,587,659,          523,440,440,0,
  587,698,880,784,698,      659,523,659,587,523,
  494,494,523,587,659,      523,440,440
};
static const uint16_t TETRIS_DURS[] PROGMEM = {
  250,125,125,250,125,125,  250,125,125,250,125,125,
  375,125,250,250,          250,250,500,250,
  375,125,250,125,125,      375,125,250,125,125,
  250,125,125,250,250,      250,250,500
};
constexpr uint8_t TETRIS_LEN = 38;

// ── Super Mario Bros ──────────────────────────────────────────
static const uint16_t MARIO_FREQS[] PROGMEM = {
  659,659,0,659,0,523,659,
  784,0,392,0,
  523,0,392,0,330,0,
  440,0,494,0,466,440,
  392,659,784,880,698,784,
  0,659,523,587,494,0
};
static const uint16_t MARIO_DURS[] PROGMEM = {
  125,125,125,125,125,125,250,
  250,250,250,500,
  375,125,250,250,375,125,
  250,125,250,125,125,250,
  167,167,167,250,125,125,
  125,250,125,125,375,125
};
constexpr uint8_t MARIO_LEN = 35;

// ── Harry Potter (Hedwig's Theme) ─────────────────────────────
static const uint16_t HP_FREQS[] PROGMEM = {
  494,659,784,740,659,
  988,880,
  740,
  659,784,740,622,
  659,
  494,659,784,740,659,
  988,1175,1047,
  988
};
static const uint16_t HP_DURS[] PROGMEM = {
  300,450,150,300,600,
  300,900,
  900,
  450,150,300,600,
  900,
  300,450,150,300,600,
  300,300,900,
  900
};
constexpr uint8_t HP_LEN = 22;

// ── Star Wars — Imperial March ────────────────────────────────
static const uint16_t SW_FREQS[] PROGMEM = {
  392,392,392,311,466,392,311,466,392,
  587,587,587,622,466,370,311,466,392
};
static const uint16_t SW_DURS[] PROGMEM = {
  400,400,400,300,100,400,300,100,800,
  400,400,400,300,100,400,300,100,800
};
constexpr uint8_t SW_LEN = 18;

// ── Pirates of the Caribbean ──────────────────────────────────
static const uint16_t PIRATES_FREQS[] PROGMEM = {
  294,330,349,392,440,466,440,392,349,330,294,
  330,349,392,440,587,440,392,440,294,0
};
static const uint16_t PIRATES_DURS[] PROGMEM = {
  200,150,150,200,150,150,200,150,150,200,400,
  150,150,200,300,300,150,150,300,400,300
};
constexpr uint8_t PIRATES_LEN = 21;

// ── Ghostbusters ──────────────────────────────────────────────
static const uint16_t GB_FREQS[] PROGMEM = {
  330,392,440,0,330,392,466,440,0,
  330,392,440,523,440,392,330,
  330,392,440,0,330,392,466,440,0,
  349,330,294,0
};
static const uint16_t GB_DURS[] PROGMEM = {
  200,200,200,100,200,200,200,400,200,
  150,150,150,300,150,150,300,
  200,200,200,100,200,200,200,400,200,
  200,200,400,400
};
constexpr uint8_t GB_LEN = 29;

// ── Nokia Ringtone ────────────────────────────────────────────
static const uint16_t NOKIA_FREQS[] PROGMEM = {
  659,587,370,415,554,494,294,330,
  494,440,277,330,440
};
static const uint16_t NOKIA_DURS[] PROGMEM = {
  125,125,250,250,125,125,250,250,
  125,125,250,250,500
};
constexpr uint8_t NOKIA_LEN = 13;

// ── DOOM (E1M1 — At Doom's Gate) ─────────────────────────────
static const uint16_t DOOM_FREQS[] PROGMEM = {
  330,330,659,330,294,330,262,330,247,0,233,0,247,0,
  330,330,659,330,294,330,262,247,0,
  330,330,659,330,294,330,262,330,247,0,233,0,247,0,
  392,0,392,0,349,0,392,0,330,0,311,0,330,0
};
static const uint16_t DOOM_DURS[] PROGMEM = {
  100,100,100,100,100,100,100,100,100,100,100,100,100,300,
  100,100,100,100,100,100,100,100,300,
  100,100,100,100,100,100,100,100,100,100,100,100,100,300,
  200,100,200,100,200,100,200,100,200,100,200,100,200,200
};
constexpr uint8_t DOOM_LEN = 51;

// ── Mortal Kombat ─────────────────────────────────────────────
static const uint16_t MK_FREQS[] PROGMEM = {
  466,466,466,466,466,466,0,
  370,415,466,0,370,415,466,0,
  466,523,466,370,0,349,370,466,0,415,466,
  466,466,466,466,466,466,0,
  370,415,466,0,370,415,466,0,
  523,466,415,370,415,466,523
};
static const uint16_t MK_DURS[] PROGMEM = {
  100,100,100,100,100,100,100,
  200,200,400,200,200,200,400,200,
  150,150,150,150,100,100,150,300,100,200,400,
  100,100,100,100,100,100,100,
  200,200,400,200,200,200,400,200,
  200,200,200,200,200,200,400
};
constexpr uint8_t MK_LEN = 48;

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

void drawMusicModeScreen() {
  display.clear();
  display.setCursor(0, 0);
  display.print(F("Mini Oda Paneli"));
  display.setCursor(0, 3);
  display.print(F("  Muzik Modu"));
  display.setCursor(0, 7);
  display.print(F("Cikis: uzun bas"));
}

void drawNowPlaying(const __FlashStringHelper* name) {
  display.setCursor(0, 5);
  display.print(F("                "));
  display.setCursor(0, 5);
  display.print(name);
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
  const bool raw = digitalRead(BUTTON_PIN) == LOW;

  switch (btnState) {
    case BTN_IDLE:
      if (raw) {
        btnState = BTN_DEBOUNCING;
        pressStartAt = now;
        longPressHandled = false;
      }
      break;

    case BTN_DEBOUNCING:
      if (!raw) {
        // Bounce — yoksay
        btnState = BTN_IDLE;
      } else if (now - pressStartAt >= 50) {
        // 50ms boyunca LOW kaldı — gerçek basış onaylandı
        btnState = BTN_PRESSED;
      }
      break;

    case BTN_PRESSED:
      if (!raw) {
        // Bırakıldı
        btnState = BTN_IDLE;
        if (!longPressHandled) {
          // Kısa basış — sessiz modu değiştir
          silentMode = !silentMode;
          Serial.print(F("Sessiz mod: "));
          Serial.println(silentMode ? F("ACIK") : F("KAPALI"));
          drawSilentModeFeedback();
          lastReadAt = 0;
        }
      } else if (!longPressHandled && now - pressStartAt >= LONG_PRESS_MS) {
        // Uzun basış — müzik modunu değiştir
        longPressHandled = true;
        musicMode = !musicMode;
        if (musicMode) {
          Serial.println(F("Muzik modu: ACIK"));
          drawMusicModeScreen();
        } else {
          Serial.println(F("Muzik modu: KAPALI"));
          noTone(BUZZER_PIN);
          lastReadAt = 0;
        }
      }
      break;
  }
}

// Gecikme sırasında butonu kontrol eder — müzik modu çıkışına izin verir
void delayWithButtonCheck(unsigned long ms) {
  const unsigned long end = millis() + ms;
  while (millis() < end) {
    updateButton();
    if (!musicMode) return;
    delay(5);
  }
}

void playMelody(const uint16_t* freqs, const uint16_t* durs, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    if (!musicMode) { noTone(BUZZER_PIN); return; }
    const uint16_t freq = pgm_read_word(&freqs[i]);
    const uint16_t dur  = pgm_read_word(&durs[i]);
    if (freq > 0) {
      tone(BUZZER_PIN, freq, dur);
    } else {
      noTone(BUZZER_PIN);
    }
    delayWithButtonCheck(dur);
  }
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

  // Müzik modu — sensörler durur, sadece buzzer + LED çalışır
  if (musicMode) {
    digitalWrite(STATUS_LED_PIN, HIGH);

    drawNowPlaying(F("Tetris"));
    playMelody(TETRIS_FREQS, TETRIS_DURS, TETRIS_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Mario"));
    playMelody(MARIO_FREQS, MARIO_DURS, MARIO_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Harry Potter"));
    playMelody(HP_FREQS, HP_DURS, HP_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Star Wars"));
    playMelody(SW_FREQS, SW_DURS, SW_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Pirates"));
    playMelody(PIRATES_FREQS, PIRATES_DURS, PIRATES_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Ghostbusters"));
    playMelody(GB_FREQS, GB_DURS, GB_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Nokia"));
    playMelody(NOKIA_FREQS, NOKIA_DURS, NOKIA_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("DOOM"));
    playMelody(DOOM_FREQS, DOOM_DURS, DOOM_LEN);
    if (!musicMode) return;

    drawNowPlaying(F("Mortal Kombat"));
    playMelody(MK_FREQS, MK_DURS, MK_LEN);
    return;
  }

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
