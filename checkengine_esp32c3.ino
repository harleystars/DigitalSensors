String s,c1,c2;
int num1,num2,low,high;

void setup() {
  Serial.begin(9600);
  delay(1000);
  low=1;
  high=0;
  Serial.println("Введите один код ошибки или `ok`:");
  pinMode(8, OUTPUT);
  digitalWrite(8,high);
  pinMode(6, INPUT); 
  pinMode(4,OUTPUT);
  pinMode(10, OUTPUT);
  
}

void loop() {

if (Serial.available() > 0) {  //если есть доступные данные считываем байт
     //incomingByte = Serial.read();
     s=Serial.readStringUntil('\n');
     c1=s[0];
     c2=s[1];
     num1=c1.toInt();
     num2=c2.toInt();
     Serial.println(c1+c2);
     //Serial.println(incomingByte, DEC);
   }


//начало CHECK- всё ОК
 if (s=="ok") { 
   digitalWrite(10,HIGH);
   digitalWrite(4,HIGH);
   delayMicroseconds(50);
   if (digitalRead(6)== HIGH){
     digitalWrite(8,high);
   }
   delay(250);

   digitalWrite(10,LOW);
   digitalWrite(4, LOW);
   delayMicroseconds(50);
   if (digitalRead(6)==LOW){
     digitalWrite(8, low); 
   }
   delay(320);
 }else{
   digitalWrite(8, low);
 }
 //конец CHECK- всё ОК


if ((num1>0 && num1<=9)&&(num2>0 && num2<=9)){
  codenum1(num1);
  delay(1000);
  codenum2(num2);
  delay(4000);
} else {
  digitalWrite(8, low);
}


//коды 13,21 начало
if (s=="13,21") {
  //delay(4000);

  //1
  code1();
  delay(1000);
  //3
  code3();
  delay(2000);

  //2
  code2();
  delay(1000);
  //1
  code1();
  delay(4000);

}else{
  digitalWrite(8, low);
}
//коды 13,21 конец


}



void code1() //1 с задержкой 500 после неё
{
  digitalWrite(10,HIGH);
  digitalWrite(4, HIGH);
  delayMicroseconds(50);
  if (digitalRead(6)== HIGH){digitalWrite(8, high);}
  delay(500);
  digitalWrite(10,LOW);
  digitalWrite(4, LOW);
  delayMicroseconds(50);
  if (digitalRead(6)==LOW){digitalWrite(8, low);}
  delay(500);
}
void code2() //2 с задержкой 500 после неё
{
  for (int i = 1; i <= 2; i++) {code1();}  
}
void code3() //3 с задержкой 500 после неё
{
 for (int i = 1; i <= 3; i++) {code1();} 
}




void codenum1(int num1) // с задержкой 500 после неё
{
 for (int i = 1; i <= num1; i++) {code1();} 
}
void codenum2(int num2) // с задержкой 500 после неё
{
 for (int i = 1; i <= num2; i++) {code1();} 
}