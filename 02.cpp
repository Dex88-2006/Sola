//#include <DS3232RTC.h>        // https://github.com/JChristensen/DS3232RTC
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DS3231.h>


LiquidCrystal_I2C lcd(0x3F,16,2);

int rele = 7;
// RTC Hodiny reálného času DS3231


DS3231 rtc;
// vytvoření proměnné pro práci s časem
RTCDateTime datumCas;

void setup() {
  lcd.init();
  lcd.backlight();
  Wire.begin();
  pinMode(rele, OUTPUT);
  // zahájení komunikace s RTC obvodem
  rtc.begin();
  // nastavení času v RTC podle času kompilace programu,
  // stačí nahrát jednou
  //rtc.setDateTime(__DATE__, "20:47:00");
  // přímé nastavení času pro RTC
  //rtc.setDateTime(__DATE__, "12:34:56");
}
void loop() {
  // načtení času z RTC do proměnné
  datumCas = rtc.getDateTime();
  // postupný tisk informací po sériové lince
lcd.setCursor ( 0, 0 );
  lcd.print(datumCas.hour);
lcd.print(" ");
  lcd.print(datumCas.minute);
lcd.print(" ");
  lcd.print(datumCas.second);
  // pauza na konci smyčky loop
  delay(1000);

  if ( (datumCas.second == 10)) { digitalWrite(rele, HIGH ); };
  if ( (datumCas.second == 15)) { digitalWrite(rele, LOW ); };

  }
