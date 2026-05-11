#include <Arduino.h>
#include <DHT.h>

constexpr uint8_t DHT_PIN = 2;
constexpr uint8_t DHT_TYPE = DHT22;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  delay(500);
  dht.begin();

  Serial.println(F("DHT22 testi basladi."));
  Serial.println(F("VCC -> 5V, GND -> GND, DATA/OUT -> D2"));
}

void loop() {
  const float humidity = dht.readHumidity();
  const float temperatureC = dht.readTemperature();

  if (isnan(humidity) || isnan(temperatureC)) {
    Serial.println(F("DHT22 okuma hatasi. Kablo/pin yonunu kontrol et."));
  } else {
    Serial.print(F("Sicaklik: "));
    Serial.print(temperatureC, 1);
    Serial.print(F(" C | Nem: "));
    Serial.print(humidity, 1);
    Serial.println(F(" %"));
  }

  delay(2000);
}
