# Mini Akıllı Oda Kontrol Paneli Projesi - Proje Amacı

## 1. Projenin Genel Amacı

Bu projenin temel amacı, bir oda veya masa ortamındaki bazı çevresel durumları takip edebilen, kullanıcıya basit uyarılar verebilen ve ortam hakkında anlaşılır bilgiler sunabilen küçük ölçekli bir akıllı kontrol sistemi geliştirmektir.

Proje, özellikle elektronik ve gömülü sistemler alanına yeni başlayan bir kişinin temel kavramları uygulamalı olarak öğrenebilmesi için tasarlanmıştır. Bu güncellenmiş dokümanda yalnızca projenin amacı değil; başlangıç seviyesinde bilinmesi gereken temel elektronik kavramları, breadboard mantığı, direnç renk kodları, güvenlik notları, VS Code + PlatformIO geliştirme ortamı ve temel test adımları da eklenmiştir.

Mini Akıllı Oda Kontrol Paneli, kullanıcının bulunduğu ortam hakkında temel bilgiler edinmesini ve bazı durumlara göre sistemin otomatik tepkiler vermesini hedefler. Bu yönüyle proje, basit bir “oda asistanı” veya “masaüstü ortam takip sistemi” olarak düşünülebilir.

---

## 2. Projenin Çıkış Noktası

Günlük hayatta bulunduğumuz ortamın sıcaklığı, nemi, ışık seviyesi veya hareket durumu gibi bilgiler çoğu zaman fark edilmez. Ancak bu bilgiler, konfor, güvenlik ve ortam düzeni açısından önemlidir.

Örneğin:

- Oda çok karanlık olduğunda kullanıcı fark etmeden uzun süre düşük ışıkta çalışabilir.
- Ortam sıcaklığı veya nemi kullanıcı konforunu etkileyebilir.
- Masaya veya belirli bir alana yaklaşan bir hareket algılandığında sistem kullanıcıyı uyarabilir.
- Kullanıcı, bulunduğu ortamın durumunu tek bir küçük panel üzerinden takip edebilir.

Bu proje, tüm bu ihtiyaçları basit ve anlaşılır bir sistemde bir araya getirmeyi amaçlar.

---

## 3. Projenin Hedefi

Projenin hedefi, karmaşık olmayan ama öğretici bir akıllı oda kontrol paneli oluşturmaktır. Bu panel, kullanıcının bulunduğu ortam hakkında bilgi verecek ve bazı durumlarda otomatik olarak tepki gösterecektir.

Proje tamamlandığında sistem genel olarak şu işlevleri yerine getirebilir:

- Ortamın sıcaklık ve nem durumunu takip etmek
- Ortamın aydınlık veya karanlık olduğunu anlamak
- Yakınlık veya hareket algılandığında kullanıcıya haber vermek
- Kullanıcıya görsel veya sesli geri bildirim sağlamak
- Ortam durumunu küçük bir bilgi ekranı mantığında sunmak
- İstenirse ilerleyen aşamalarda daha gelişmiş bir oda asistanına dönüştürülebilmek

Bu hedefler sayesinde proje yalnızca basit bir deneme çalışması olmaktan çıkar; kullanıcıya gerçek anlamda fayda sağlayan küçük bir sistem haline gelir.

---

## 4. Projenin Kullanım Senaryosu

Bu proje masa üzerinde, çalışma alanında, öğrenci odasında veya küçük bir atölye ortamında kullanılabilecek şekilde düşünülmüştür.

Örnek bir kullanım senaryosu şu şekildedir:

Kullanıcı çalışma masasına oturduğunda sistem ortamı takip etmeye başlar. Eğer oda karanlıksa sistem bunu algılar ve kullanıcıya ortamın karanlık olduğunu bildirir. Kullanıcı isterse bu duruma göre masa lambasını açabilir veya ortam aydınlatmasını değiştirebilir.

Aynı zamanda sistem ortam sıcaklığını ve nem seviyesini takip eder. Kullanıcı bu değerleri ekranda görerek odanın konforlu olup olmadığını anlayabilir. Eğer sistem hareket veya yakınlık algılarsa bunu bir uyarı olarak kullanıcıya bildirir.

Bu yapı sayesinde proje, kullanıcının bulunduğu alanı daha bilinçli şekilde kontrol etmesine yardımcı olur.

---

## 5. Projenin Çözmeyi Amaçladığı Problem

Bu proje büyük ve karmaşık bir problemi çözmek için değil, temel seviyede günlük yaşamda karşılaşılabilecek küçük ama faydalı ihtiyaçlara cevap vermek için geliştirilir.

Çözmeyi amaçladığı temel problemler şunlardır:

### 5.1 Ortam Durumunu Takip Etme Eksikliği

Kullanıcılar çoğu zaman bulundukları ortamın sıcaklık, nem veya ışık durumunu anlık olarak takip etmez. Bu proje, bu bilgileri kullanıcıya düzenli şekilde sunmayı amaçlar.

### 5.2 Basit Uyarı Mekanizması Eksikliği

Bir alanda hareket veya yakınlık algılandığında kullanıcıya basit bir uyarı verilmesi bazı durumlarda faydalı olabilir. Proje, bu tür olayları algılayıp kullanıcıya bildirmeyi hedefler.

### 5.3 Elektronik Öğrenme Sürecinde Proje Eksikliği

Elektronik öğrenmeye yeni başlayan kişiler genellikle tek tek küçük denemeler yapar. Örneğin yalnızca ışık yakmak, yalnızca sensör okumak veya yalnızca ekrana yazı yazdırmak gibi parçalı çalışmalar yapılır. Bu proje ise bu küçük denemeleri anlamlı bir bütün içinde birleştirir.

Bu sayede kullanıcı sadece tekil denemeler yapmaz; gerçek bir sistem mantığı kurmayı öğrenir.

---

## 6. Projenin Eğitimsel Amacı

Bu projenin en önemli amaçlarından biri öğretici olmasıdır. Proje, başlangıç seviyesindeki bir kişinin adım adım gelişmesini sağlayacak şekilde kurgulanmıştır.

Proje sayesinde kullanıcı şu becerileri kazanabilir:

- Bir sistemin amacını belirleme
- Bir problemi küçük parçalara ayırma
- Giriş ve çıkış mantığını anlama
- GND, 5V, 3.3V gibi temel elektronik kavramlarını öğrenme
- Breadboard üzerinde bağlantı mantığını kavrama
- Direnç renk kodlarını ayırt edebilme
- VS Code + PlatformIO ile Arduino tabanlı proje geliştirme
- Kütüphane kurulumu ve sensör test adımlarını öğrenme
- Veriye göre karar verme mantığını öğrenme
- Basit bir otomasyon sisteminin nasıl çalıştığını kavrama
- Kullanıcıya geri bildirim veren bir sistem tasarlama
- Proje geliştirme sürecini aşamalı olarak deneyimleme

Burada amaç yalnızca çalışan bir cihaz ortaya çıkarmak değildir. Asıl amaç, kullanıcının sistem düşüncesi kazanmasıdır.

Yani kullanıcı şu mantığı öğrenir:

“Bir ortamdan bilgi alınır, bu bilgi değerlendirilir ve sonuca göre sistem bir tepki verir.”

Bu mantık, akıllı ev sistemlerinden robotik projelere, güvenlik sistemlerinden endüstriyel otomasyona kadar birçok alanda kullanılan temel bir yaklaşımdır.

---

## 7. Projenin Genel Çalışma Mantığı

Proje, ortamdan bazı bilgiler alır ve bu bilgilere göre kullanıcıya çıktı üretir.

Genel mantık şu şekilde açıklanabilir:

1. Sistem ortamı izler.
2. Ortamdan gelen bilgiler değerlendirilir.
3. Belirlenen koşullar kontrol edilir.
4. Koşula göre kullanıcıya bilgi veya uyarı verilir.
5. Sistem bu işlemi sürekli olarak tekrar eder.

Örneğin:

- Ortam karanlıksa sistem bunu kullanıcıya bildirir.
- Ortam sıcaklığı belirli bir seviyeye geldiyse kullanıcı bilgilendirilir.
- Yakınlık veya hareket algılanırsa sistem uyarı verir.
- Normal durumda sistem sadece ortam bilgilerini göstermeye devam eder.

Bu yapı, projenin basit ama anlamlı bir otomasyon sistemi gibi çalışmasını sağlar.

---

## 8. Projenin Kullanıcıya Sağlayacağı Faydalar

Bu proje kullanıcıya hem pratik hem de eğitimsel fayda sağlar.

### 8.1 Pratik Faydalar

- Kullanıcı ortam hakkında hızlı bilgi alabilir.
- Odanın sıcaklık, nem ve ışık durumu takip edilebilir.
- Hareket veya yakınlık durumunda uyarı alınabilir.
- Masa üstünde küçük bir bilgi paneli gibi kullanılabilir.
- İleride daha gelişmiş akıllı oda sistemlerine temel oluşturabilir.

### 8.2 Eğitimsel Faydalar

- Proje geliştirme alışkanlığı kazandırır.
- Elektronik projelere giriş için anlamlı bir başlangıç sağlar.
- Basit otomasyon mantığını öğretir.
- Donanım ve yazılımın birlikte nasıl çalıştığını anlamaya yardımcı olur.
- Kullanıcıyı daha gelişmiş projelere hazırlar.

---

## 9. Projenin Kapsamı

Bu proje başlangıç seviyesinde bir akıllı oda kontrol sistemidir. Kapsamı bilinçli olarak sınırlı tutulmuştur. Böylece proje hem öğrenilebilir hem de tamamlanabilir hale gelir.

Projenin temel kapsamı şunlardır:

- Ortam durumunun takip edilmesi
- Kullanıcıya bilgi gösterilmesi
- Belirli durumlarda uyarı verilmesi
- Yakınlık veya hareket algılamaya bağlı tepki oluşturulması
- Projenin masa üstü veya oda içi kullanım için tasarlanması

Proje şu anda büyük ölçekli bir akıllı ev sistemi olarak düşünülmemelidir. Örneğin evdeki tüm lambaları, kapıları, prizleri veya cihazları kontrol eden kapsamlı bir sistem değildir. Bunun yerine küçük, güvenli, anlaşılır ve öğrenmeye uygun bir prototip olarak ele alınmalıdır.

---

## 10. Projenin Kapsam Dışı Bıraktığı Konular

Bu dokümanda ve projenin ilk aşamasında bazı konular özellikle kapsam dışında bırakılmıştır.

Kapsam dışı konular:

- Gerçek ev elektriği kontrolü
- Priz, ampul veya yüksek voltajlı cihaz kontrolü
- 220V şehir elektriğiyle çalışma
- Röle ile gerçek ev cihazı kontrolü
- Karmaşık kablosuz haberleşme sistemleri
- Mobil uygulama geliştirme
- İnternet üzerinden uzaktan kontrol
- Gelişmiş güvenlik sistemi özellikleri
- Profesyonel ürün tasarımı
- Endüstriyel otomasyon seviyesi kontrol

Bu sınırlandırma, projenin daha güvenli ve öğrenmeye uygun kalmasını sağlar.

Önemli not: Bu projenin ilk aşamasında yalnızca düşük voltajlı, USB veya güvenli adaptörle beslenen Arduino tabanlı devreler düşünülmelidir. Priz, ampul, ev elektriği veya yüksek akım taşıyan cihazlarla çalışılmamalıdır.

---

## 11. Projenin Geliştirilebilir Yönleri

Bu proje tamamlandıktan sonra daha gelişmiş hale getirilebilir. İlk sürüm temel bir oda kontrol paneli olarak çalışırken, ilerleyen sürümlerde daha fazla özellik eklenebilir.

Geliştirilebilir fikirler:

- Kablosuz bağlantı eklenerek verilerin telefondan görüntülenmesi
- Web panel üzerinden ortam bilgilerinin izlenmesi
- Günlük sıcaklık ve nem kayıtlarının tutulması
- Belirli eşik değerlerine göre otomatik uyarılar oluşturulması
- Daha şık bir kutu tasarımı yapılması
- Farklı odalar için çoklu takip sistemi geliştirilmesi
- Basit bir güvenlik modu eklenmesi
- Kullanıcının ayar yapabileceği küçük bir menü sistemi oluşturulması

Bu geliştirmeler sayesinde proje, zamanla daha profesyonel bir akıllı oda sistemine dönüştürülebilir.

---

## 12. Projenin Başlangıç Seviyesi İçin Uygunluğu

Bu proje özellikle başlangıç seviyesi için uygundur çünkü çok karmaşık bir hedef koymaz. Kullanıcıdan ileri düzey elektronik bilgisi beklemez. Proje adım adım ilerletilebilir.

İlk aşamada sadece basit bir gösterge veya uyarı sistemi kurulabilir. Daha sonra sıcaklık, nem, ışık, hareket ve ekran gibi özellikler sırayla eklenebilir. Böylece kullanıcı her aşamada bir şey öğrenir ve öğrendiklerini bir sonraki aşamada kullanır.

Bu yaklaşım, öğrenme sürecini daha kontrollü ve anlaşılır hale getirir.

---

## 13. Projenin Gerçek Hayattaki Karşılığı

Mini Akıllı Oda Kontrol Paneli, büyük akıllı ev sistemlerinin küçük ve basitleştirilmiş bir örneği olarak görülebilir.

Gerçek hayatta benzer sistemler şu alanlarda kullanılır:

- Akıllı ev sistemleri
- Oda iklimlendirme kontrolü
- Basit güvenlik sistemleri
- Laboratuvar ortam takibi
- Ofis konfor izleme sistemleri
- Endüstriyel ortam sensör sistemleri
- Otomasyon eğitim setleri

Bu proje, bu alanlardaki temel mantığı küçük ölçekte deneyimlemeyi sağlar.

---

## 14. Projenin Nihai Amacı

Projenin nihai amacı, kullanıcının kendi başına anlayabileceği, geliştirebileceği ve açıklayabileceği basit ama anlamlı bir akıllı oda sistemi ortaya çıkarmaktır.

Bu proje sonunda kullanıcı yalnızca bir cihaz yapmış olmayacak; aynı zamanda şu sorulara cevap verebilecek seviyeye gelecektir:

- Bir ortam takip sistemi nasıl düşünülür?
- Sistem hangi verileri toplamalıdır?
- Toplanan veriler nasıl yorumlanmalıdır?
- Kullanıcıya hangi durumlarda bilgi verilmelidir?
- Basit bir otomasyon sistemi nasıl planlanır?
- Bir proje küçük aşamalara nasıl bölünür?

Bu nedenle proje, sadece teknik bir deneme değil, aynı zamanda sistem tasarımı ve problem çözme çalışmasıdır.

---

## 15. V1 Donanım ve Pin Planı

İlk çalışan sürüm, Arduino Uno R3 ve iki büyük breadboard üzerinde kurulacak düşük voltajlı bir masaüstü prototipidir. Bu sürümde amaç tüm sistemi tek seferde karmaşık hale getirmek değil; her modülü ayrı ayrı test edip sonra güvenli şekilde birleştirmektir.

### 15.1 Kullanılacak Ana Parçalar

| Parça | Görev |
|---|---|
| Arduino Uno R3 | Sistemin ana kontrol kartı |
| 2 büyük breadboard | Modüllerin lehimsiz kurulumu |
| DHT22 | Sıcaklık ve nem ölçümü |
| LDR ışık sensörü kartı | Ortam aydınlık/karanlık algılama |
| HC-SR501 PIR | Hareket algılama |
| I2C SH1106 OLED 128x64 | Bilgi ekranı |
| Pasif buzzer | Sesli uyarı |
| LED + 220/330 ohm direnç | Görsel uyarı |
| Jumper kablolar | Breadboard ve Arduino bağlantıları |

### 15.2 Arduino Uno Pin Atama Tablosu

| Arduino pini | Bağlanacak parça | Açıklama |
|---|---|---|
| D2 | DHT22 DATA | Sıcaklık/nem veri pini |
| D3 | HC-SR501 OUT | Hareket algılama dijital çıkışı |
| D4 | LDR modül DO | Dijital ışık/karanlık çıkışı |
| A4 | OLED SDA | I2C veri hattı |
| A5 | OLED SCK / SCL | I2C saat hattı |
| D5 | KY-004 buton S | Sessiz mod aç/kapat |
| D6 | HC-SR04 TRIG | Mesafe sensörü tetik pini |
| D7 | HC-SR04 ECHO | Mesafe sensörü yankı pini |
| D8 | Harici LED | Görsel uyarı çıkışı |
| D9 | Pasif buzzer | `tone()` ile ses üretimi |
| D13 | Dahili LED | Blink ve hızlı kart testi |
| 5V | Breadboard + hattı | Modül besleme hattı |
| GND | Breadboard - hattı | Ortak toprak hattı |

### 15.3 Breadboard Güç Düzeni

Fotoğraflarda iki büyük breadboardun yan yana birleştirildiği görülmektedir. Bu geniş alan proje için uygundur; ancak güç rayları otomatik olarak birbirine bağlı kabul edilmemelidir.

Kurulumda şu düzen kullanılmalıdır:

- Arduino `5V` pini, breadboard kırmızı `+` hattına bağlanır.
- Arduino `GND` pini, breadboard mavi `-` hattına bağlanır.
- Birinci breadboardun `+` hattı ile ikinci breadboardun `+` hattı jumper ile köprülenir.
- Birinci breadboardun `-` hattı ile ikinci breadboardun `-` hattı jumper ile köprülenir.
- Eğer güç rayları ortadan kesintiliyse üst ve alt segmentler ayrıca köprülenir.
- Güç vermeden önce multimetre ile `5V` ve `GND` arasında kısa devre olmadığı kontrol edilir.

### 15.4 Modül Bağlantı Notları

- DHT22 çıplak sensör olarak kullanılıyorsa `DATA` ile `VCC` arasına `10K` pull-up direnç eklenir. Hazır DHT22 modüllerinde bu direnç çoğu zaman kart üzerinde bulunur.
- Kullanılan LDR kartında `VCC`, `GND` ve `DO` pinleri vardır. `VCC` kırmızı `+` hattına, `GND` mavi `-` hattına, `DO` Arduino `D4` pinine bağlanır. Bu modülde ayrı `10K` direnç kullanılmaz.
- Harici LED doğrudan Arduino pinine bağlanmamalıdır; seri olarak `220 ohm` veya `330 ohm` direnç kullanılmalıdır.
- Pasif buzzer küçük piezo tipindeyse `D9` ve `GND` arasında test edilebilir. Daha fazla akım çeken bir buzzer çıkarsa transistorlü sürücü devresi kullanılmalıdır.
- Kullanılan OLED ekranda `SCK` yazısı `SCL` hattı gibi kullanılmaktadır. Arduino bağlantısı `SDA -> A4`, `SCK/SCL -> A5` şeklindedir.
- OLED ekran SH1106 uyumlu çalışmıştır. RAM tasarrufu için final V1 kodunda tam grafik tamponu kullanan SSD1306 yaklaşımı yerine U8x8 metin modu kullanılmalıdır.
- HC-SR501 PIR sensörü açılıştan sonra kısa bir ısınma süresi ister. İlk saniyelerde gelen hareket bilgisi kararsız olabilir.

---

## 16. Bağlantı ve Test Kontrol Listesi

Kod ve devre birlikte kurulmadan önce her parça ayrı ayrı test edilmelidir. Böylece bir hata olduğunda hangi modülden kaynaklandığı daha kolay anlaşılır.

### 16.1 Güvenli Başlangıç Kontrolü

- Arduino USB kablosu takılı değilken breadboard bağlantıları yapılır.
- `5V` ve `GND` hatları gözle kontrol edilir.
- Multimetre ile `5V` ve `GND` arasında kısa devre olmadığı doğrulanır.
- Breadboard güç raylarının tüm kullanılan segmentlerinde süreklilik kontrol edilir.
- Arduino yalnızca USB veya güvenli düşük voltajlı adaptör ile beslenir.
- Priz, 220V, röle, motor veya yüksek akım çeken yük kullanılmaz.

### 16.2 PlatformIO Ortam Tablosu

`platformio.ini` içindeki her ortam (`env`) tek bir test dosyasını veya final kodu derler. Bu yapı sayesinde her modül bağımsız olarak yüklenip test edilebilir.

| PlatformIO Ortamı | Kaynak Dosya | Açıklama |
|---|---|---|
| `uno` | `main.cpp` | **Final V2 kodu** — tüm modüller entegre |
| `led_test` | `led_test.cpp` | D8 LED blink testi |
| `buzzer_test` | `buzzer_test.cpp` | D9 pasif buzzer ton testi |
| `ldr_test` | `ldr_test.cpp` | A0 analog LDR değeri okuma |
| `ldr_module_test` | `ldr_module_test.cpp` | D4 dijital LDR modül (DO) testi |
| `dht22_test` | `dht22_test.cpp` | D2 DHT22 sıcaklık/nem testi |
| `oled_test` | `oled_test.cpp` | SSD1306 kütüphanesiyle ilk OLED denemesi |
| `oled_sh1106_combo_test` | `oled_sh1106_combo_test.cpp` | Adafruit SH1106 kütüphanesi + LED + buzzer |
| `room_panel_test` | `room_panel_test.cpp` | DHT22 + SH1106 OLED entegrasyon ara test |
| `room_panel_u8x8_test` | `room_panel_u8x8_test.cpp` | DHT22 + U8x8 metin modu + PIR ara test |
| `button_test` | `button_test.cpp` | D5 KY-004 buton + LED + buzzer testi |

Karta yüklemek için VS Code alt çubuğundaki ortam adı seçilir; örneğin `[env:dht22_test]` seçilip **Upload** yapılır.

### 16.3 Sıralı Modül Testleri

1. Arduino Uno bağlantısı ve PlatformIO upload testi yapılır.
2. `D13` dahili LED ile Blink testi yapılır.
3. Harici LED, dirençle birlikte `D8` üzerinde `led_test` ortamıyla test edilir.
4. Pasif buzzer `D9` üzerinde `buzzer_test` ortamıyla kısa `tone()` denemesi yapılır.
5. LDR modülünün `DO` çıkışı `D4` üzerinde `ldr_module_test` ortamıyla test edilir; aydınlık/karanlık durumunda `HIGH/LOW` değişimi izlenir.
6. DHT22 sıcaklık ve nem okuması `dht22_test` ortamıyla ayrı test edilir.
7. I2C scanner kodu elle yüklenerek OLED adresi doğrulanır (beklenen: `0x3C`).
8. `oled_sh1106_combo_test` ortamıyla OLED üzerinde yazı ve sayaç gösterimi test edilir.
9. HC-SR501 PIR sensörü hareket var/yok bilgisiyle `room_panel_u8x8_test` ortamında izlenir.
10. HC-SR04 ultrasonik sensör D6/D7 pinlerine bağlanarak mesafe ölçümü Serial Monitor'dan doğrulanır.
11. KY-004 butonu D5 pinine bağlanarak `button_test` ortamıyla basma/bırakma ve buzzer tonu doğrulanır.
12. Tüm modüller birlikte bağlanarak `uno` ortamıyla V2 entegrasyon testi yapılır.

### 16.4 V2 Entegrasyon Kabul Kriterleri

V2 sistemin çalışır kabul edilmesi için şu davranışlar görülmelidir:

- Serial Monitor sıcaklık, nem, ışık, hareket, mesafe, yakın nesne ve sessiz mod durumunu düzenli yazdırır.
- OLED ekran tüm ortam bilgilerini 2 saniyede bir günceller.
- Ortam karanlık olduğunda veya HC-SR04 ≤30 cm nesne algıladığında `D8` LED yanar.
- Hareket algılandığında veya nesne 30 cm içine girdiğinde, sessiz mod kapalıysa buzzer 6 saniyede bir kısa bip verir.
- KY-004 butona basıldığında sessiz mod açılır/kapanır; OLED geçici geri bildirim ekranı gösterir.
- Sessiz modda buzzer susturulur; OLED son satırda `Sessiz mod` görünür.
- DHT22 okuma hatası olduğunda sistem kilitlenmez; ekranda `hata` bilgisi gösterilir.
- PIR sensörü açılış ısınma süresinde (30 s) ekranda hareket için `BEKLE` görünür.

### 16.5 Final V2 Yazılım Davranışı

Final V2 kodu `src/main.cpp` içindedir ve PlatformIO `uno` ortamı ile derlenir. Test dosyaları klasörde kalsa da `build_src_filter` sayesinde `uno` ortamına dahil edilmez.

Serial başlangıç mesajı:

```text
Mini Akilli Oda Kontrol Paneli V2
DHT22 D2 | PIR D3 | LDR D4 | Button D5 | HC-SR04 D6/D7 | LED D8 | Buzzer D9
```

OLED ekranı (8 satır × 16 karakter, U8x8 metin modu):

```text
Mini Oda Paneli        satır 0
                       satır 1 (boş)
Sicaklik: XX.X C       satır 2
Nem:      XX.X %       satır 3
                       satır 4 (boş)
Isik: AYDINLIK/KARANLIK  satır 5
Har:VAR/YOK M:XXcm    satır 6
Sessiz mod / LED aktif / Buzzer aktif / Durum normal  satır 7
```

V2 uyarı mantığı:

- **LED (D8):** Karanlık VEYA nesne ≤30 cm ise yanar.
- **Buzzer (D9):** Hareket VAR VEYA nesne ≤30 cm ise, sessiz mod kapalıysa 6 s aralıkla 1200 Hz / 35 ms bip verir.
- **HC-SR04 mesafe:** 25 ms zaman aşımıyla ölçülür; sinyal gelmezse `-1` (ekranda `--`) gösterilir.
- **Buton debounce:** 120 ms kararlılık + 800 ms toggle kilidi ile çift tetikleme önlenir.
- **PIR ısınma:** İlk 30 s ekranda `BEKLE`, Serial'da `isiniyor` görünür.
- **OLED kütüphanesi:** RAM dostu U8x8 metin modu kullanılır (Arduino Uno R3'ün 2 KB RAM sınırı nedeniyle tam grafik tamponu tercih edilmez).

---

## 17. Başlangıç Seviyesi İçin Temel Elektronik Kavramları

Bu projede elektronik bilgisi olmayan bir kullanıcının da adım adım ilerleyebilmesi hedeflenmiştir. Bu yüzden GND, 5V, 3.3V, VCC, sinyal pini ve kısa devre gibi kavramlar temel seviyede bilinmelidir.

### 17.1 GND Nedir?

**GND**, devrenin ortak referans noktasıdır.

Basitçe:

> Devredeki tüm parçaların “ortak eksi hattı” gibi düşünülebilir.

Arduino, sensör ve modüllerin birbirini doğru anlayabilmesi için genellikle GND hatları ortak bağlanır.

Örneğin:

- Arduino GND
- DHT11 / DHT22 GND
- LDR devresi GND
- OLED ekran GND
- Buzzer GND

aynı hatta bağlanmalıdır.

GND ortak değilse sensörlerden gelen veriler hatalı okunabilir veya sistem hiç çalışmayabilir.

### 17.2 5V Nedir?

**5V**, Arduino Uno gibi kartlarda kullanılan yaygın besleme voltajıdır.

Bazı modüller 5V ile çalışabilir:

- Bazı LCD ekranlar
- Bazı buzzer modülleri
- Bazı mesafe sensörleri
- Bazı röle modülleri

Ancak her modül 5V ile çalışmaz. Bu yüzden modülün çalışma voltajı kontrol edilmelidir.

### 17.3 3.3V Nedir?

**3.3V**, özellikle modern sensörlerde sık kullanılan bir besleme voltajıdır.

Bazı modüller sadece 3.3V ile çalışabilir. Bu modüllere doğrudan 5V vermek modülü bozabilir.

Bu projede kullanılabilecek bazı sensör veya modüller 3.3V seviyesinde çalışabilir. Bu yüzden her modül için şu sorular sorulmalıdır:

1. Bu modül 5V ile mi çalışıyor?
2. Bu modül 3.3V ile mi çalışıyor?
3. Hem 3.3V hem 5V destekliyor mu?
4. Üzerinde voltaj regülatörü var mı?

### 17.4 VCC Nedir?

**VCC**, modülün güç girişidir.

Bir sensör üzerinde şu pinler görülebilir:

- VCC
- GND
- DATA

VCC pinine modülün desteklediği voltaj verilmelidir.

Örneğin modül 5V destekliyorsa Arduino 5V pinine bağlanabilir. Modül sadece 3.3V destekliyorsa Arduino 3.3V pinine bağlanmalıdır.

### 17.5 Sinyal Pini Nedir?

Sinyal pini, modül ile Arduino arasında veri taşıyan pindir.

Örneğin:

- DHT sensöründe DATA pini
- LDR devresinde analog okuma pini
- HC-SR04 sensöründe TRIG ve ECHO pinleri
- OLED ekranda SDA ve SCL pinleri

Bu pinler güç pini değildir. Veri taşırlar.

### 17.6 Kısa Devre Nedir?

Kısa devre, elektrik akımının gitmemesi gereken bir yoldan doğrudan akmasıdır.

En basit örnek:

> 5V ile GND’nin doğrudan bağlanması kısa devredir.

Bu durumda:

- Arduino reset atabilir.
- USB portu zarar görebilir.
- Kablo veya kart ısınabilir.
- Sensör bozulabilir.
- Bilgisayarın USB portu risk altına girebilir.

Bu yüzden bağlantı yaparken özellikle 5V, 3.3V ve GND hatlarına çok dikkat edilmelidir.

### 17.7 Ters Bağlama Nedir?

Ters bağlama, güç bağlantılarının yanlış yapılmasıdır.

Örneğin:

- VCC yerine GND bağlamak
- GND yerine 5V bağlamak
- 3.3V isteyen modüle 5V vermek
- Artı ve eksi uçları karıştırmak

Ters bağlantı bazı modülleri anında bozabilir.

---

## 18. Breadboard Nasıl Çalışır?

Breadboard, lehim yapmadan devre kurmayı sağlayan deneme kartıdır.

Başlangıçta karmaşık görünebilir ama mantığı basittir.

### 18.1 Breadboard Üzerindeki Güç Hatları

Breadboard’un kenarlarında genellikle kırmızı ve mavi çizgiler bulunur.

Genel kullanım:

- Kırmızı çizgi: + güç hattı
- Mavi veya siyah çizgi: GND hattı

Ancak önemli nokta şudur:

> Breadboard üzerindeki kırmızı çizgi kendiliğinden 5V değildir.  
> Mavi çizgi de kendiliğinden GND değildir.

Arduino 5V pinini kırmızı hatta bağlarsan o hat 5V olur. Arduino GND pinini mavi hatta bağlarsan o hat GND olur.

### 18.2 Orta Kısımdaki Bağlantı Mantığı

Breadboard’un orta kısmındaki delikler genellikle 5’li gruplar halinde birbirine bağlıdır.

Örneğin:

```text
A B C D E    F G H I J
```

- A-B-C-D-E aynı satırda kendi içinde bağlıdır.
- F-G-H-I-J aynı satırda kendi içinde bağlıdır.
- Ortadaki boşluk iki tarafı birbirinden ayırır.

Bu yüzden bir sensörün bacakları veya direnç uçları doğru satırlara takılmalıdır.

### 18.3 En Sık Yapılan Breadboard Hataları

Başlangıçta en sık yapılan hatalar şunlardır:

- 5V ve GND hattını yanlışlıkla birleştirmek
- Sensörü bir satır kaydırarak takmak
- Breadboard güç hattının ortadan bölünmüş olduğunu fark etmemek
- Aynı satırda sanıp aslında farklı satıra bağlantı yapmak
- VCC ve GND pinlerini ters bağlamak
- SDA ve SCL pinlerini karıştırmak
- DATA pinini yanlış Arduino pinine bağlamak

### 18.4 Basit LED Testi

İlk breadboard pratiği olarak LED yakma yapılabilir.

Genel bağlantı mantığı:

```text
Arduino dijital pin → direnç → LED uzun bacak
LED kısa bacak → GND
```

LED doğrudan Arduino pinine bağlanmamalıdır. Araya direnç konulmalıdır.

Genelde 220 ohm veya 330 ohm direnç kullanılabilir.

---

## 19. Direnç Renk Kodu Rehberi

Elektronik başlangıç kitlerinde çok sayıda direnç bulunur. Bu dirençleri ayırt etmek için renk kodları bilinmelidir.

### 19.1 En Çok Kullanılan Dirençler

| Direnç | Kullanım Alanı |
|---:|---|
| 220 ohm | LED koruma |
| 330 ohm | LED koruma |
| 1K ohm | Genel amaçlı devreler |
| 4.7K ohm | Bazı sensör ve haberleşme devreleri |
| 10K ohm | Buton, LDR, pull-up / pull-down |
| 100K ohm | Gerilim bölücü gibi uygulamalar |

### 19.2 Renklerin Sayısal Karşılığı

| Renk | Sayı | Çarpan |
|---|---:|---:|
| Siyah | 0 | x1 |
| Kahverengi | 1 | x10 |
| Kırmızı | 2 | x100 |
| Turuncu | 3 | x1.000 |
| Sarı | 4 | x10.000 |
| Yeşil | 5 | x100.000 |
| Mavi | 6 | x1.000.000 |
| Mor | 7 | x10.000.000 |
| Gri | 8 | x100.000.000 |
| Beyaz | 9 | x1.000.000.000 |

### 19.3 4 Bantlı Direnç Okuma

4 bantlı dirençlerde:

1. bant: ilk rakam
2. bant: ikinci rakam
3. bant: çarpan
4. bant: tolerans

Örnek:

**Kırmızı - Kırmızı - Kahverengi - Altın**

- Kırmızı = 2
- Kırmızı = 2
- Kahverengi = x10
- Altın = ±5%

Sonuç:

```text
22 x 10 = 220 ohm
```

### 19.4 Yaygın Direnç Renkleri

| Değer | Renk Kodu |
|---:|---|
| 220 ohm | Kırmızı - Kırmızı - Kahverengi |
| 330 ohm | Turuncu - Turuncu - Kahverengi |
| 1K ohm | Kahverengi - Siyah - Kırmızı |
| 4.7K ohm | Sarı - Mor - Kırmızı |
| 10K ohm | Kahverengi - Siyah - Turuncu |
| 100K ohm | Kahverengi - Siyah - Sarı |

### 19.5 Multimetre Kullanma Tavsiyesi

Renk kodları bazen karışabilir. Özellikle 500 parçalık kitlerde renkler birbirine çok benzeyebilir.

Bu yüzden mümkünse dirençler multimetre ile ölçülerek doğrulanmalıdır.

---

## 20. Arduino: Orijinal ve Klon Farkı

Bu proje için kullanıcının **orijinal Arduino** aldığı varsayılmıştır. Bu başlangıç için avantajdır.

### 20.1 Orijinal Arduino Neden Avantajlıdır?

Orijinal Arduino kartlarda genellikle:

- Sürücü problemi daha az olur.
- Bilgisayar kartı daha kolay tanır.
- USB bağlantısı daha stabil olur.
- Kart kalitesi daha güvenilirdir.
- Başlangıçta hata ayıklamak daha kolaydır.

Bu yüzden ilk projelerde orijinal Arduino kullanmak öğrenme sürecini kolaylaştırabilir.

### 20.2 Klon Arduino Nedir?

Klon Arduino, Arduino tasarımına benzer şekilde üretilen ama farklı üreticilerden çıkan kartlardır.

Klon kartlar genellikle daha ucuzdur. Ancak bazı klonlarda farklı USB-serial çipi bulunur.

Örneğin:

- CH340
- CH341
- CP2102

Bu durumda bilgisayar kartı tanımayabilir ve ayrıca sürücü kurmak gerekebilir.

### 20.3 Gelecekte Klon Arduino Kullanılırsa

İleride klon Arduino kullanılırsa şunlara dikkat edilmelidir:

- Kart görünmüyorsa CH340 / CH341 sürücüsü gerekebilir.
- USB kablosu sadece şarj kablosu olabilir.
- Doğru COM port seçilmelidir.
- Bazı klonların 3.3V çıkışı zayıf olabilir.
- Kalitesiz klonlarda bağlantı kopmaları yaşanabilir.

---

## 21. Geliştirme Ortamı: Direkt VS Code + PlatformIO

Bu proje için önce Arduino IDE ile başlayıp sonra VS Code’a geçmek zorunlu değildir.

Kullanıcı doğrudan **VS Code + PlatformIO** ile başlayıp aynı ortamda devam edebilir.

Bu tercih sorun oluşturmaz. Hatta proje büyüdükçe daha düzenli bir yapı sağlar.

### 21.1 Neden VS Code + PlatformIO?

VS Code + PlatformIO kullanmanın avantajları:

- Proje klasör yapısı daha düzenlidir.
- Kütüphaneler proje bazlı yönetilir.
- `platformio.ini` dosyası ile kart, framework ve kütüphaneler net tanımlanır.
- Kod tamamlama daha gelişmiştir.
- GitHub ile çalışmak daha rahattır.
- Büyük projelerde dosyaları ayırmak daha kolaydır.
- İleride ESP32 veya STM32 gibi kartlara geçmek daha sistemli olur.

Arduino IDE daha basit görünebilir ama uzun vadeli proje mantığında VS Code + PlatformIO daha güçlü bir seçenektir.

### 21.2 Kurulum Adımları

1. VS Code indir ve kur.
2. VS Code içinde Extensions bölümünü aç.
3. **PlatformIO IDE** eklentisini ara.
4. PlatformIO IDE eklentisini kur.
5. VS Code’u yeniden başlat.
6. Sol tarafta PlatformIO ikonu görünmelidir.

### 21.3 İlk Proje Oluşturma

Arduino Uno için:

1. VS Code’u aç.
2. PlatformIO ikonuna tıkla.
3. **PIO Home** ekranına gir.
4. **New Project** seç.
5. Project Name alanına örneğin şunu yaz:

```text
mini_akilli_oda_paneli
```

6. Board kısmında şunu seç:

```text
Arduino Uno
```

7. Framework kısmında şunu seç:

```text
Arduino
```

8. Finish butonuna bas.

### 21.4 PlatformIO Klasör Yapısı

PlatformIO projesinde genellikle şu yapı olur:

```text
mini_akilli_oda_paneli/
│
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
└── platformio.ini
```

En önemli dosyalar:

| Dosya / Klasör | Açıklama |
|---|---|
| `src/main.cpp` | Ana kod dosyası |
| `platformio.ini` | Kart, framework, port ve kütüphane ayarları |
| `lib/` | Projeye özel yerel kütüphaneler |
| `include/` | Header dosyaları |
| `test/` | Test dosyaları |

### 21.5 PlatformIO Blink Testi

PlatformIO’da Arduino kodu genelde `src/main.cpp` içine yazılır.

Örnek Blink kodu:

```cpp
#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

### 21.6 platformio.ini Örneği

Arduino Uno için temel `platformio.ini` dosyası:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 9600
```

Bu dosya şunu ifade eder:

- Platform: AVR tabanlı Arduino
- Kart: Arduino Uno
- Framework: Arduino
- Serial Monitor hızı: 9600 baud

### 21.7 Kod Derleme, Yükleme ve Seri Port

PlatformIO’da temel işlemler:

| İşlem | PlatformIO Komutu |
|---|---|
| Derleme | Build |
| Karta yükleme | Upload |
| Seri port izleme | Monitor |
| Temiz derleme | Clean |

Eğer PlatformIO portu otomatik bulamazsa `platformio.ini` içine şu satır eklenebilir:

```ini
upload_port = COM3
```

Windows’ta portlar genellikle COM3, COM4, COM5 gibi görünür.

---

## 22. PlatformIO ile Kütüphane Kurulumu

Sensörleri kullanmak için PlatformIO projesine kütüphane eklemek gerekir.

### 22.1 Library Ekranı ile Kurulum

1. VS Code içinde PlatformIO ikonuna tıkla.
2. **Libraries** bölümüne gir.
3. Arama kutusuna sensörün veya modülün adını yaz.
4. Uygun kütüphaneyi seç.
5. **Add to Project** butonuna bas.
6. İlgili projeyi seç.
7. PlatformIO gerekli satırı `platformio.ini` dosyasına ekler.

### 22.2 platformio.ini ile Kütüphane Ekleme

Kütüphaneler elle de eklenebilir.

Örnek:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 9600

lib_deps =
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
    olikraus/U8g2
```

Bu yöntem avantajlıdır çünkü proje başka bilgisayara taşındığında PlatformIO kütüphaneleri otomatik indirir.

### 22.3 Bu Projede Kullanılabilecek Kütüphaneler

| Modül / Sensör | PlatformIO’da Aranabilecek Kütüphane |
|---|---|
| DHT11 / DHT22 | DHT sensor library |
| OLED ekran | U8g2 |
| SH1106 metin ekranı | U8x8 |
| I2C haberleşme | Wire |
| Servo motor | Servo |
| SD kart | SD |
| RTC saat modülü | RTClib |

### 22.4 Kütüphane Hatası Alınırsa

Eğer şu hata görülürse:

```text
No such file or directory
```

Muhtemel sebepler:

- Kütüphane `platformio.ini` içine eklenmemiştir.
- Kütüphane adı yanlış yazılmıştır.
- Kütüphanenin bağımlılığı eksiktir.
- PlatformIO kütüphaneleri henüz indirmemiştir.
- Proje yeniden build edilmelidir.

---

## 23. I2C Scanner Kodu

OLED ekran, bazı sensörler ve bazı modüller I2C haberleşme kullanabilir.

I2C cihazları kullanırken en büyük sorunlardan biri cihaz adresini bilmemektir. I2C Scanner kodu bağlı I2C cihazlarını tarar ve adreslerini seri porta yazar.

### 23.1 Arduino Uno I2C Pinleri

Arduino Uno için:

| Hat | Arduino Uno Pini |
|---|---|
| SDA | A4 |
| SCL | A5 |
| VCC | Modüle göre 3.3V veya 5V |
| GND | GND |

### 23.2 I2C Scanner Kodu

```cpp
#include <Arduino.h>
#include <Wire.h>

void setup() {
  Wire.begin();

  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("I2C Scanner baslatildi.");
}

void loop() {
  byte error;
  byte address;
  int deviceCount = 0;

  Serial.println("Taranıyor...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C cihaz bulundu. Adres: 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);
      deviceCount++;
    } 
    else if (error == 4) {
      Serial.print("Bilinmeyen hata. Adres: 0x");

      if (address < 16) {
        Serial.print("0");
      }

      Serial.println(address, HEX);
    }
  }

  if (deviceCount == 0) {
    Serial.println("I2C cihaz bulunamadi.");
  } else {
    Serial.print(deviceCount);
    Serial.println(" adet I2C cihaz bulundu.");
  }

  Serial.println();
  delay(5000);
}
```

### 23.3 Beklenen Çıktı Örneği

```text
I2C Scanner baslatildi.
Taranıyor...
I2C cihaz bulundu. Adres: 0x3C
1 adet I2C cihaz bulundu.
```

OLED ekranlar genellikle `0x3C` adresinde görülebilir. Bazı modüller farklı adreslerde olabilir.

---

## 24. Güvenlik Notları

Bu proje düşük voltajlı bir öğrenme projesi olarak düşünülmelidir.

### 24.1 Bağlantı Yaparken Gücü Kes

Bağlantı değiştirirken Arduino’nun USB kablosu çıkarılmalıdır.

Kural:

> Önce bağlantıyı yap, sonra güç ver.  
> Bağlantıyı değiştireceksen önce gücü kes.

### 24.2 5V ve GND’yi Doğrudan Birleştirme

5V ile GND doğrudan bağlanırsa kısa devre olur.

Bu durumda:

- Arduino reset atabilir.
- Kart ısınabilir.
- USB portu zarar görebilir.
- Modül bozulabilir.

### 24.3 3.3V Modüle 5V Verme

Bazı modüller sadece 3.3V ile çalışır.

Bu modüllere 5V vermek bozulmalarına neden olabilir.

Her modül için ürün sayfasından çalışma voltajı kontrol edilmelidir.

### 24.4 Ev Elektriği Kullanılmamalı

Bu projenin başlangıç aşamasında:

- Priz kontrolü yapılmamalı.
- 220V şehir elektriği kullanılmamalı.
- Ampul, fan, ısıtıcı gibi yüksek voltajlı cihazlar bağlanmamalı.
- Röle ile ev cihazı kontrolüne girilmemeli.

Bunlar tehlikelidir ve başlangıç seviyesi için uygun değildir.

### 24.5 Güvenli Test Yaklaşımı

İlk testlerde gerçek cihazlar yerine şunlar kullanılmalıdır:

- LED
- Buzzer
- OLED ekran
- Serial Monitor çıktısı
- Düşük voltajlı sensörler

Sistem doğru çalıştıktan sonra bile yüksek voltajlı cihazlara geçilmemelidir.

---

## 25. Güncellenmiş Öğrenme Sırası

Bu projede önerilen güncel öğrenme sırası şu şekildedir:

1. GND, 5V, 3.3V, VCC ve kısa devre kavramlarını öğren.
2. Breadboard bağlantı mantığını öğren.
3. Direnç renk kodlarını öğren.
4. VS Code + PlatformIO kurulumunu yap.
5. Arduino Uno için PlatformIO projesi oluştur.
6. Blink testi yap.
7. Breadboard üzerinde LED yak.
8. Serial Monitor kullanımını öğren.
9. LDR veya basit bir sensör okuma denemesi yap.
10. DHT11 / DHT22 ile sıcaklık ve nem oku.
11. I2C Scanner kodu ile OLED ekran adresini bul.
12. OLED ekrana veri yazdır.
13. Hareket veya yakınlık sensörü ekle.
14. Koşula göre LED / buzzer uyarısı ver.
15. Sistemi küçük bir akıllı oda paneli haline getir.

Bu sıralama ile proje hem güvenli hem de anlaşılır şekilde ilerler.

---

## 26. Kısa Proje Tanımı

Mini Akıllı Oda Kontrol Paneli, bulunduğu ortamı takip ederek kullanıcıya sıcaklık, nem, ışık ve hareket/yakınlık durumu hakkında bilgi veren küçük ölçekli bir akıllı ortam izleme sistemidir. Proje, başlangıç seviyesindeki kullanıcıların temel otomasyon mantığını öğrenmesi ve ileride daha gelişmiş akıllı sistemler geliştirebilmesi için tasarlanmıştır.

---

## 27. Özet

Bu proje, elektronik öğrenmeye yeni başlayan bir kişi için hem öğretici hem de motive edici bir başlangıç projesidir. Projenin amacı karmaşık bir cihaz üretmek değil, basit ama anlamlı bir sistem kurarak kullanıcının temel otomasyon mantığını kavramasını sağlamaktır.

Mini Akıllı Oda Kontrol Paneli; ortamı izleyen, duruma göre karar veren ve kullanıcıya bilgi sunan küçük bir sistemdir. Bu yönüyle hem günlük yaşama dokunan bir fikir sunar hem de daha gelişmiş projelere geçmek için sağlam bir temel oluşturur.
