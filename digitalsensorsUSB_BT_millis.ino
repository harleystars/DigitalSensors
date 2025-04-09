#include <EEPROM.h>
#include <iarduino_VCC.h>

#define B 3950 // B-коэффициент
#define SERIAL_R 39000 // сопротивление постоянного резистора, 39 кОм
#define THERMISTOR_R 43000 // номинальное сопротивления термистора, 43 кОм
#define NOMINAL_T 25 // номинальная температура (при которой сопротивление термистора = 43 кОм)
#define speedk 2548 //количество импульсов датчика скорости на 1км
#define maslo 5000 //пробег до замены масла в км
#define filtr 5000 //пробег до замены воздушного фильтра в км

unsigned long timing; // Переменная для хранения точки отсчета, для паузы меджу выводами значений в сериал

volatile byte ChangeInt = false;
volatile byte ChangeInt1 = false;
volatile uint32_t CountInt = 0; 
volatile uint32_t CountIntF = 0; 
uint32_t CountEEPROM_read = 0;
uint32_t CountEEPROM_readF = 0;
int16_t voltalert = 0;
bool flagwrite=false;
bool resetmaslo=false;
bool resetfiltr=false;
String air, oil;


void setup() {
  Serial.begin(9600);
  air ="0000";
  oil ="0000";

  pinMode(A0,INPUT);  //пин А0, чтение напряжения, датчик давления
  pinMode(A1,INPUT);  //пин А1, чтение напряжения, термистор/датчик температуры
  
  EEPROM.get(0, CountEEPROM_read);
  EEPROM.get(4, CountEEPROM_readF);
  CountInt=CountEEPROM_read;
  CountIntF=CountEEPROM_readF;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT); 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT); 
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), counterObjects, RISING);
 
  Serial.println(CountInt);
  Serial.println(CountIntF);
  flagwrite=false;
  resetmaslo=false;
  resetfiltr=false;
  if (CountInt-1000000000>10){
  //if (CountInt-1000000000>speedk*maslo){
    digitalWrite(4, HIGH);
    air="1111k";
  }else{
    digitalWrite(4, LOW);
    air="0000k";
  }
  if (CountIntF-1000000000>17){
  //if (CountIntF-1000000000>speedk*filtr){
    digitalWrite(5, HIGH);
    oil="1111kend";
  }else{
    digitalWrite(5, LOW);
    oil="0000kend";
  }

  delay (1700);
}

void loop() {
   voltalert = analogRead_VCC();
  if ((voltalert<3.8) && (flagwrite==false)){
    EEPROM.put(0, CountInt);
    EEPROM.put(4, CountIntF);   
    flagwrite = true;  
  }

  //Проверки кнопок сброса пробегов на фильт и масло , пины D6,D7
  if ((digitalRead(6) == LOW) && resetmaslo==false) 
  { 
    digitalWrite(4, LOW);
    CountInt=1000000000;

    resetmaslo=true;  
  }
  if ((digitalRead(7) == LOW) && resetfiltr==false) 
  { 
    digitalWrite(5, LOW);
    CountIntF=1000000000;
    resetfiltr=true;  
  }

   //задержка с которой происходит обновление в сериал значений температуры и давления
  if (millis() - timing > 1500){ // Вместо 1500 подставьте нужное вам значение паузы 
  timing = millis(); 

  //Чтение, обработка и пересчет показаний с термистора NTC, пин А1 (взято из инета)
    int t = analogRead(A1);
    // float v1 = (float)(t * 5.0) / 1024;      //напряжение на пине датчика температуры
    float tr = 1023.0 / t - 1;
    tr = SERIAL_R / tr;
    float st;
    st = tr / THERMISTOR_R; // (R/Ro)
    st = log(st); // ln(R/Ro)
    st /= B; // 1/B * ln(R/Ro)
    st += 1.0 / (NOMINAL_T + 273.15); // + (1/To)
    st = 1.0 / st; // Invert
    st -= 273.15; 

  //const float BETA = 3950; // should match the Beta Coefficient of the thermistor
  //double celsius = 1 / (log(1 / (1023. / tempraw - 1)) / BETA + 1.0 / 298.15) - 273.15;

  // float v2 = (float)(analogRead(A0) * 5.0) / 1024;      //напряжение на пине датчика давления
  float Pressure=map(analogRead(A0),96,920,0,150);      //давление в psi, пересчет дан для датчика на 150psi, заменить последнее число в map на значение датчика
  float kpa = Pressure*6.9/100;                         //пересчет давления в кПа
  
  if (analogRead(A1)>900) 
  {Serial.print("begintalarmk");}
   else 
   {Serial.print("begin"+String(st,0)+"k");} //вывод значения температуры в градусах цельсия в serial порт
   
  if (analogRead(A0)>750)
  {Serial.print("palarmk");}
  //{Serial.println("palarmkend");}
  else
  {Serial.print(String(kpa,2)+"k");} //вывод значения давления в kPa в serial порт 
  //{Serial.println(String(kpa,2)+"kend");} //вывод значения давления в kPa в serial порт 

  Serial.println(air+oil);
  //Serial.println("end");


  // long randNumber = random(300);
  // if (randNumber < 150){ 
  // Serial.println("1111k1111kend");}
  // else {Serial.println("0000k0000kend");}

 
 }
}

void counterObjects() 
{
  if (digitalRead(2) == HIGH) 
  { 
    CountInt++;
    CountIntF++;  
    ChangeInt = true;                        
  }
}