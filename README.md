# Mini Akıllı Oda Kontrol Paneli / Mini Smart Room Control Panel

Arduino Uno R3 tabanlı, masaüstü ortam izleme ve kontrol sistemi.  
An Arduino Uno R3 based desktop environment monitoring and control system.

---

## 🇹🇷 Türkçe

### Proje Hakkında

Bu proje, bulunduğum odanın sıcaklık, nem, ışık ve hareket gibi çevresel verilerini gerçek zamanlı olarak izleyen, OLED ekranda görüntüleyen ve belirli koşullarda LED ile buzzer aracılığıyla uyarı veren küçük ölçekli bir akıllı oda kontrol panelidir.

Projeyi geliştirirken her modülü ayrı ayrı test ettim, karşılaştığım sorunları adım adım çözdüm ve sistemi V1'den V2'ye taşıdım.

### Özellikler

- Sıcaklık ve nem ölçümü (DHT22)
- Ortam aydınlık/karanlık algılama (LDR modülü)
- Hareket algılama (HC-SR501 PIR)
- Mesafe ölçümü (HC-SR04 ultrasonik)
- OLED ekranda gerçek zamanlı bilgi gösterimi (SH1106 128x64)
- Karanlık veya yakın nesne varsa LED uyarısı
- Hareket veya yakın nesne varsa buzzer uyarısı
- Buton ile sessiz mod (KY-004)

### Donanım

| Parça | Pin |
|---|---|
| DHT22 | D2 |
| HC-SR501 PIR | D3 |
| LDR modül DO | D4 |
| KY-004 buton S | D5 |
| HC-SR04 TRIG | D6 |
| HC-SR04 ECHO | D7 |
| LED + 220Ω | D8 |
| Pasif buzzer | D9 |
| OLED SDA | A4 |
| OLED SCL | A5 |

### Kurulum

1. [PlatformIO IDE](https://platformio.org/) kurulu VS Code gereklidir.
2. Repoyu klonla:
   ```
   git clone https://github.com/mustaffadnC/mini-smart-room-panel.git
   ```
3. VS Code'da projeyi aç.
4. Arduino'yu USB ile bağla (COM6).
5. PlatformIO alt çubuğundan `env:uno` seç ve **Upload** yap.

### Proje Yapısı

```
arduino/
├── src/
│   ├── main.cpp               # Final V2 kodu
│   ├── led_test.cpp           # LED blink testi
│   ├── buzzer_test.cpp        # Buzzer ton testi
│   ├── ldr_test.cpp           # Analog LDR testi
│   ├── ldr_module_test.cpp    # Dijital LDR modül testi
│   ├── dht22_test.cpp         # DHT22 sıcaklık/nem testi
│   ├── oled_test.cpp          # SSD1306 OLED testi
│   ├── oled_sh1106_combo_test.cpp  # SH1106 + LED + buzzer testi
│   ├── room_panel_test.cpp    # DHT22 + SH1106 entegrasyon testi
│   ├── room_panel_u8x8_test.cpp   # U8x8 metin modu testi
│   └── button_test.cpp        # KY-004 buton bağlantı testi
├── platformio.ini
└── mini_akilli_oda_kontrol_paneli_guncellenmis.md
```

### OLED Ekran Düzeni

```
Mini Oda Paneli
[boş]
Sicaklik: 22.7 C
Nem:      49.2 %
[boş]
Isik: AYDINLIK
Har:YOK M:124cm
Durum normal
```

### Geliştirme Süreci

| Gün | Yapılan |
|---|---|
| 1. Gün | Proje planı, parça listesi, breadboard düzeni |
| 2. Gün | LED, buzzer ve LDR modül testleri |
| 3. Gün | DHT22 ve OLED (SSD1306 → SH1106) testleri |
| 4. Gün | PIR ve HC-SR04 mesafe sensörü entegrasyonu |
| 5. Gün | V1: Tüm modüllerin ilk entegrasyonu, U8x8 geçişi |
| 6. Gün | V2: HC-SR04 + buton/sessiz mod eklendi, alert mantığı güncellendi |
| 7. Gün | Buton bağlantısı ve INPUT_PULLUP ile debounce çözümü, dokümantasyon |

---

## 🇬🇧 English

### About

This is a small-scale smart room control panel based on Arduino Uno R3. It monitors environmental data (temperature, humidity, light, motion, distance) in real time, displays it on an OLED screen, and triggers LED/buzzer alerts under certain conditions.

Each module was tested independently before integration. The project evolved from V1 (basic sensor panel) to V2 (adding ultrasonic distance sensing, silent mode button, and improved alert logic).

### Features

- Temperature & humidity measurement (DHT22)
- Ambient light detection (LDR module)
- Motion detection (HC-SR501 PIR)
- Distance measurement (HC-SR04 ultrasonic)
- Real-time OLED display (SH1106 128x64, U8x8 text mode)
- LED alert on darkness or close object (≤30 cm)
- Buzzer alert on motion or close object (silent mode available)
- Silent mode toggle via push button (KY-004, INPUT_PULLUP wiring)

### Hardware

| Component | Pin |
|---|---|
| DHT22 | D2 |
| HC-SR501 PIR | D3 |
| LDR module DO | D4 |
| KY-004 button S | D5 |
| HC-SR04 TRIG | D6 |
| HC-SR04 ECHO | D7 |
| LED + 220Ω | D8 |
| Passive buzzer | D9 |
| OLED SDA | A4 |
| OLED SCL | A5 |

### Setup

1. Install [VS Code](https://code.visualstudio.com/) with [PlatformIO IDE](https://platformio.org/).
2. Clone the repo:
   ```
   git clone https://github.com/mustaffadnC/mini-smart-room-panel.git
   ```
3. Open the project in VS Code.
4. Connect Arduino via USB (COM6 or your port).
5. Select `env:uno` in the PlatformIO toolbar and click **Upload**.

### Key Technical Notes

- **OLED:** SH1106 controller (not SSD1306). U8x8 text mode is used to stay within Arduino Uno's 2 KB RAM limit.
- **Button wiring:** KY-004 S pin → D5, middle pin → GND, `-` pin → GND. Uses `INPUT_PULLUP` — no external resistor needed.
- **Debounce:** Immediate rising edge detection with 200 ms ignore window. No lock timer.
- **V2 LED logic:** ON when dark OR object ≤ 30 cm.
- **V2 buzzer logic:** Beeps when motion OR object ≤ 30 cm, every 6 s, 1200 Hz / 35 ms.

### PlatformIO Environments

| Environment | Source | Purpose |
|---|---|---|
| `uno` | `main.cpp` | **Final V2** — all modules integrated |
| `led_test` | `led_test.cpp` | LED blink test |
| `buzzer_test` | `buzzer_test.cpp` | Buzzer tone test |
| `ldr_test` | `ldr_test.cpp` | Analog LDR read |
| `ldr_module_test` | `ldr_module_test.cpp` | Digital LDR module |
| `dht22_test` | `dht22_test.cpp` | DHT22 sensor |
| `oled_test` | `oled_test.cpp` | SSD1306 initial test |
| `oled_sh1106_combo_test` | `oled_sh1106_combo_test.cpp` | SH1106 + LED + buzzer |
| `room_panel_test` | `room_panel_test.cpp` | DHT22 + SH1106 integration |
| `room_panel_u8x8_test` | `room_panel_u8x8_test.cpp` | U8x8 text mode test |
| `button_test` | `button_test.cpp` | Button wiring diagnostic |

### License

MIT
