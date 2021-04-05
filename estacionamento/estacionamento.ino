/*
*  Estacionamento
*  Código Arduino para simular um display que informa se a vaga está disponível ou não
*  para isso é utilizado  um sensor ultrassônico
*  Autor: Prof. Wender Firmino - wender@unesc.net
*/

#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 13, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define trig1 7
#define echo1 6
 
void setup()
{
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2); 
} 
 
void loop()
{
  long duration1, distance1;
  digitalWrite(trig1,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);


  duration1 = pulseIn(echo1, HIGH);
  distance1 = duration1 * 0.034 / 2;
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("-=[VAGA]=-");  

  if (distance1 >= 100){
    lcd.setCursor(0,1);
    lcd.print("LIVRE");
    delay(1000);
  }
  else if (distance1 < 30){
    lcd.setCursor(0,1);
    lcd.print("OCUPADA");
    delay(1000);
  }
  delay(1000);     
}
