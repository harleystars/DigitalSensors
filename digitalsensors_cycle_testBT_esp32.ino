#include "BluetoothSerial.h"
//#define B 3950 // B-коэффициент
//#define SERIAL_R 39000 // сопротивление постоянного резистора, 39 кОм
//#define THERMISTOR_R 43000 // номинальное сопротивления термистора, 43 кОм
//#define NOMINAL_T 25 // номинальная температура (при которой сопротивление термистора = 43 кОм)
int st =1;
float kpa = 0.1;
int i;
int r;
int kpa1;
String st1;

BluetoothSerial ESP_BT;

void setup() {
  Serial.begin(9600);
  ESP_BT.begin("HC-ESP32");
  //pinMode(A0,INPUT);  //режим пина А0 с подтяжкой по питанию, чтение напряжения, датчик давления
 // pinMode(A1,INPUT);  //пин А1, чтение с него напряжения, термистор/датчик температуры
 }

void loop() {

//if (ESP_BT.available())
 
//{
 while (i<130)
 {
  st=st+1;
  kpa=kpa+0.1;
  // kpa1=kpa*100;
  //  st1 = toString st;
  //  kpa1 = toString kpa;

  ESP_BT.println("begin"+String(st)+"k"+String(kpa,2)+"cend");
  Serial.println("begin"+String(st)+"k"+String(kpa,2)+"cend");
  //ESP_BT.print(st);
  //ESP_BT.print("k");
  //ESP_BT.println(kpa1);
  //Serial.print(st);
  //Serial.print("k");
  //Serial.println(kpa1);
  
  //ESP_BT.print(st); //вывод значения температуры в градусах цельсия в serial порт
  //ESP_BT.print("k"); 
  //ESP_BT.print(kpa,2); //вывод значения давления в kPa в serial порт (вместо kpa поставить необходимую переменную bar или Pressure)
  //ESP_BT.print("c");
  //ESP_BT.println("end");
  delay(1000); //задержка с которой происходит обновлние значений температуры и давления
  i++;
 }

for (r=130; r>1; r--)
{
  st=st-1;
  kpa=kpa-0.1;
  //kpa1=kpa*100;

  ESP_BT.println("begin"+String(st)+"k"+String(kpa,2)+"cend");
  Serial.println("begin"+String(st)+"k"+String(kpa,2)+"cend");
  //ESP_BT.print(st);
  //ESP_BT.print("k");
  //ESP_BT.println(kpa1);
  //Serial.print(st);
  //Serial.print("k");
  //Serial.println(kpa1);
  //ESP_BT.print("begin");
  //ESP_BT.print(st); //вывод значения температуры в градусах цельсия в serial порт
  //ESP_BT.print("k"); 
  //ESP_BT.print(kpa,2); //вывод значения давления в kPa в serial порт (вместо kpa поставить необходимую переменную bar или Pressure)
  //ESP_BT.print("c");
  //ESP_BT.println("end");
  delay(1000); //задержка с которой происходит обновление значений температуры и давления
  ESP_BT.flush();
  Serial.flush();
}
}
