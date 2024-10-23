#define B 3950 // B-коэффициент
#define SERIAL_R 39000 // сопротивление постоянного резистора, 39 кОм
#define THERMISTOR_R 43000 // номинальное сопротивления термистора, 43 кОм
#define NOMINAL_T 25 // номинальная температура (при которой сопротивление термистора = 43 кОм)

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);  //режим пина А0 с подтяжкой по питанию, чтение напряжения, датчик давления
  pinMode(A1,INPUT);  //пин А1, чтение с него напряжения, термистор/датчик температуры
 }

void loop() {
 
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
  float bar = Pressure*0.069;                           //пересчет давления в Бар
  float kpa = Pressure*6.9/100;                         //пересчет давления в кПа

  if (analogRead(A1)>900) 
  {Serial.print("talarm"); 
    Serial.print("k");}
   else 
   {Serial.print(st,0); //вывод значения температуры в градусах цельсия в serial порт
    Serial.print("k"); }

  if (analogRead(A0)>750)
  {Serial.print("palarm");
   Serial.println("c");}
  else
  {Serial.print(kpa,2); //вывод значения давления в kPa в serial порт (вместо kpa поставить необходимую переменную bar или Pressure)
  Serial.println("c");}
  
  delay(1500); //задержка с которой происходит обновлние значений температуры и давления
}
