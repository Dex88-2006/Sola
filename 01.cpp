#include <arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>
#include <DS3231.h>


LiquidCrystal_I2C lcd(0x3F,20,4);
const int pinCidlaDS = 8;
OneWire oneWireDS(pinCidlaDS);
DallasTemperature senzoryDS(&oneWireDS);
float TP1;
//bazen
float TP2;
//panel
int rele = 14;
int SEPNUTI = 0;
int releState = 0;
bool flag1 = true;

DS3231 rtc;
// vytvoření proměnné pro práci s časem
RTCDateTime datumCas;

elapsedMillis debounce;
elapsedMillis timerCerpadlo;
elapsedMillis timerCerpadlo2;
int TPB = 30;
int TPS = 32;
int valve2 = 15;
int valve1 = 16;
byte pinBazen = 5;
//plus
byte pinPanel = 6;
//minus
byte pinSelect = 4;
byte pinScreen = 3;

;
void setup(void) {
  senzoryDS.begin();
  lcd.init();
  lcd.backlight();
  Wire.begin();
  // zahájení komunikace s RTC obvodem
  rtc.begin();
  // nastavení času v RTC podle času kompilace programu,
  // stačí nahrát jednou
  //rtc.setDateTime(__DATE__, "17:30:40");
  // přímé nastavení času pro RTC
  //rtc.setDateTime(__DATE__, "12:34:56");
  pinMode(rele,OUTPUT);
  pinMode(pinBazen,INPUT_PULLUP);
  pinMode(pinPanel,INPUT_PULLUP);
  pinMode(pinSelect,INPUT_PULLUP);
  pinMode(pinScreen,INPUT_PULLUP);
  digitalWrite(14, HIGH) ;
}
void loop(void) {
  releState = digitalRead(rele);
  // načtení času z RTC do proměnné
  datumCas = rtc.getDateTime();
  // postupný tisk informací po sériové lince

  senzoryDS.requestTemperatures();
  TP1 = senzoryDS.getTempCByIndex(0);
  TP2 = senzoryDS.getTempCByIndex(1);
  lcd.setCursor ( 0, 0 );
  lcd.print("--Bazen--  --Panel--");
  lcd.setCursor ( 0, 1 );
  lcd.print(TP1, 1);
  lcd.print(" (");
  lcd.print(TPB);
  lcd.print(")");
  lcd.setCursor ( 11, 1 );
  lcd.print(TP2, 1);
  lcd.print(" (");
  lcd.print(TPS);
  lcd.print(")");
  lcd.setCursor ( 0, 2 );
  lcd.print(" Cas  Pumpa  Ventil");
  lcd.setCursor ( 0, 3 );
  lcd.print(datumCas.hour);
  lcd.print(":");
  lcd.print(datumCas.minute);
  lcd.print(":");
  lcd.print(datumCas.second);
  lcd.setCursor ( 8, 3 );
  if (releState == LOW) {

            lcd.print(" on");
            }

            else {

                  lcd.print("off");

}


if ((TP2>TPS)) {
 timerCerpadlo = 0;
 digitalWrite(rele,LOW);}

 if(timerCerpadlo>100000 && flag1){
digitalWrite(rele,HIGH);
//SEPNUTI++;

}



  if (digitalRead(pinBazen) == LOW  && (digitalRead(pinSelect) == HIGH)  && debounce > 500){
  TPB++;
  debounce=0;
  }

  else if(digitalRead(pinBazen) == LOW && (digitalRead(pinSelect) == LOW) && debounce > 500){
  TPB--;
  debounce=0;
  }

  if (digitalRead(pinPanel) == LOW && (digitalRead(pinSelect) == HIGH) && debounce > 500){
  TPS++;
  debounce=0;
  }

  else if(digitalRead(pinPanel) == LOW && (digitalRead(pinSelect) == LOW) && debounce > 500){
  TPS--;
  debounce=0;
  }

  if ( (datumCas.hour == 7) && (datumCas.minute == 0)) { digitalWrite(valve1, HIGH ); };
  if ( (datumCas.hour == 7) && (datumCas.minute == 1)) { digitalWrite(valve1, LOW ); };

  if ( (datumCas.hour == 19) && (datumCas.minute == 30)) { digitalWrite(valve2, HIGH ); };
  if ( (datumCas.hour == 19) && (datumCas.minute == 31)) { digitalWrite(valve2, LOW ); };


  if ( (datumCas.second == 1)) {
    flag1 = false;
    timerCerpadlo2 = 0;
    digitalWrite(rele, LOW );
   }

   if(timerCerpadlo2 > 6000){
   digitalWrite(rele,HIGH);
   flag1 =  true;

   }
   
}
