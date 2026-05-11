#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

constexpr uint8_t SCREEN_WIDTH = 128;
constexpr uint8_t SCREEN_HEIGHT = 64;
constexpr int8_t OLED_RESET_PIN = -1;
constexpr uint8_t OLED_ADDRESS = 0x3C;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println(F("OLED testi basladi."));
  Serial.println(F("GND -> GND, VCC -> 5V, SCK/SCL -> A5, SDA -> A4"));

  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("OLED baslatilamadi. Adres veya kablo kontrol et."));
    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("OLED calisiyor"));
  display.println(F("Mini Oda Paneli"));
  display.println();
  display.println(F("SDA -> A4"));
  display.println(F("SCK -> A5"));
  display.display();
}

void loop() {
  static unsigned long counter = 0;

  display.fillRect(0, 50, SCREEN_WIDTH, 14, SSD1306_BLACK);
  display.setCursor(0, 54);
  display.print(F("Sayac: "));
  display.print(counter++);
  display.display();

  Serial.println(F("OLED ekran guncellendi."));
  delay(1000);
}
