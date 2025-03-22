#include "EEPROM.h"
volatile byte ChangeInt=false;
volatile int16_t CountInt=0;
volatile int16_t CountEEPROM=0;
int16_t CountEEPROM_read=0;
int voltalert=0;
int analogPin =0;
int volt=0;




void setup() {
  EEPROM.get(0, CountEEPROM_read);
  CountInt=CountEEPROM_read;
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2),counterObject, FALLING);
  EEPROM.get(5,voltalert);
  EEPROM.get(0,CountEEPROM_read);
  Serial.println(voltalert);
  Serial.println(CountEEPROM_read);
  
}

void loop() {
  volt =analogRead(analogPin);
  //Serial.print(volt);
  if (volt<1022) {
    EEPROM.update(5,999);
    }
  if (digitalRead(2) == HIGH){digitalWrite(LED_BUILTIN, LOW);}
  else {digitalWrite(LED_BUILTIN, HIGH);}
  }

void counterObject()
{
  if (digitalRead(2)==LOW)
  {
    CountInt++;
    ChangeInt = true;
    if (CountInt%10 ==0){
      EEPROM.put(0,CountInt);
      EEPROM.get(0,CountEEPROM_read);
      Serial.print("from EEPROM ");
      Serial.println(CountEEPROM_read);
    }
  }
}


