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
float SEPNUTI = 0;
int status = false;

elapsedMillis debounce;
elapsedMillis timerCerpadlo;
float TPB = 28;
float TPS = 40;
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
  pinMode(rele,OUTPUT);
  pinMode(pinBazen,INPUT_PULLUP);
  pinMode(pinPanel,INPUT_PULLUP);
  pinMode(pinSelect,INPUT_PULLUP);
  pinMode(pinScreen,INPUT_PULLUP);


}
void loop(void) {

 if (status==1) {

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


}

  if(status==0) {

  lcd.setCursor ( 0, 0 );
  lcd.print("----");
  lcd.setCursor ( 2, 1 );
  lcd.print("----");
  lcd.setCursor ( 13, 1 );
  lcd.print("----");
  lcd.setCursor ( 0, 2 );
  lcd.print("---");
  lcd.setCursor ( 2, 3 );
  lcd.print("--");
  lcd.setCursor ( 13, 3 );
  lcd.print("--");
  lcd.clear();
  }



  if (TP2<TPS+1){
 timerCerpadlo = 0;
 digitalWrite(rele,HIGH);}

 if(timerCerpadlo>180000){
digitalWrite(rele,LOW);
SEPNUTI++;}



  if (digitalRead(pinBazen) == LOW && (digitalRead(pinSelect) == HIGH) && debounce > 500){
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


  if (digitalRead(pinScreen) == true && debounce > 500) { status = !status;
    debounce=0;
 }


}
