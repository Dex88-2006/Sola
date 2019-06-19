#include <arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>


LiquidCrystal_I2C lcd(0x3F,20,4);
const int pinCidlaDS = 8;
OneWire oneWireDS(pinCidlaDS);
DallasTemperature senzoryDS(&oneWireDS);
float TP1;
//bazen
float TP2;
//panel
int rele = 13;

elapsedMillis debounce;
float TPB = 28;
float TPS = 40;
byte pinBazen = 3;
//plus
byte pinPanel = 4;
//minus
byte pinSelect = 5;
byte pinScreen = 6;

;
void setup(void) {
  senzoryDS.begin();
  lcd.init();
  lcd.backlight();
  pinMode(rele,OUTPUT);
  pinMode(pinBazen,INPUT);
  pinMode(pinPanel,INPUT);
  pinMode(pinSelect,INPUT);
  pinMode(pinScreen,INPUT);

}
void loop(void) {

  senzoryDS.requestTemperatures();
  TP1 = senzoryDS.getTempCByIndex(0);
  TP2 = senzoryDS.getTempCByIndex(1);
  lcd.setCursor ( 0, 0 );
  lcd.print("--Bazen--  --Panel--");
  lcd.setCursor ( 2, 1 );
  lcd.print(TP1);
  lcd.setCursor ( 13, 1 );
  lcd.print(TP2);
  lcd.setCursor ( 0, 2 );
  lcd.print("---Max---  ---Max---");
  lcd.setCursor ( 2, 3 );
  lcd.print(TPB);
  lcd.setCursor ( 13, 3 );
  lcd.print(TPS);

  if (TP2<TPS){
  digitalWrite(rele,HIGH);}
  else {digitalWrite(rele,LOW);}


  if (digitalRead(pinBazen == HIGH) && (digitalRead(pinSelect) == LOW) && debounce > 500){
  TPB++;
  debounce=0;
  }

  else if(digitalRead(pinBazen) && (digitalRead(pinSelect) == HIGH) && debounce > 500){
  TPB--;
  debounce=0;
  }

  if (digitalRead(pinPanel == HIGH) && (digitalRead(pinSelect) == LOW) && debounce > 500){
  TPB++;
  debounce=0;
  }

  else if(digitalRead(pinPanel) && (digitalRead(pinSelect) == HIGH) && debounce > 500){
  TPB--;
  debounce=0;
  }

}
