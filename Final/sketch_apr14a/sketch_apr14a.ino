#include <Wire.h>               // I2C函式庫
#include <LiquidCrystal_PCF8574.h>
const int P1AgreePin = 13; 
const int P1DisagreePin = 12; 
const int P2AgreePin = 11; 
const int P2DisagreePin = 10; 
const int P3AgreePin = 9; 
const int P3DisagreePin = 8; 
const int BuzzerPin = 7; 
int resistor1, resistor2, resistor3;
int P1AgreeBtnSt, P1DisagreeBtnSt, P2AgreeBtnSt, P2DisagreeBtnSt, P3AgreeBtnSt, P3DisagreeBtnSt;
int P1Showup, P2Showup, P3Showup;   // 可以出現在議場的立委0代表不行1可以
LiquidCrystal_PCF8574 lcd(0x27);
String FirstLine = "WWelcome to NTUST LiFaUan";
String ShowupList = "SShowup List: ";
String Alarm = "ALERT: ";
String Alarm2 = "No show but vote";

String P1 = "English Tsai";
String P2 = "KP";
String P3 = "Korea Han";

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(BuzzerPin,OUTPUT); //digitalWrite(7,HIGH) or LOW;
  pinMode(P1AgreePin, INPUT);
  pinMode(P1DisagreePin, INPUT);
  pinMode(P2AgreePin, INPUT);
  pinMode(P2DisagreePin, INPUT);
  pinMode(P3AgreePin, INPUT);
  pinMode(P3DisagreePin, INPUT);
  Serial.begin(9600);
  P1Showup=0, P2Showup=1, P3Showup=0;
  if (P1Showup==1) {
    ShowupList += P1;
  } else if (P2Showup==1) {
    ShowupList += P2;
  } else if (P3Showup==1) {
    ShowupList += P3;
  } 

  lcd.begin(16, 2); // 初始化LCD
  lcd.setBacklight(255);
  lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("NTUST LiFaUan");
  // lcd.setCursor(0,1);
  // lcd.print("");
}
int prev=0;
void loop()
{
  resistor1=analogRead(A0); 
  resistor2=analogRead(A1); 
  resistor3=analogRead(A2);
  P1AgreeBtnSt= digitalRead(P1AgreePin);
  P1DisagreeBtnSt= digitalRead(P1DisagreePin);
  P2AgreeBtnSt= digitalRead(P2AgreePin);
  P2DisagreeBtnSt= digitalRead(P2DisagreePin);
  P3AgreeBtnSt= digitalRead(P3AgreePin);
  P3DisagreeBtnSt= digitalRead(P3DisagreePin);
  Alarm = "ALERT: ";

  // for (int i = 1; i <= FirstLine.length(); i++) {
  //   lcd.setCursor(0, 0);
  //   lcd.print(FirstLine.substring(i + 1, FirstLine.length()));  //每次迴圈把字串往後遞減一格來選取，並顯示到最後一個字
  //   lcd.print(" ");
  //   lcd.setCursor(0, 1);
  //   lcd.print(ShowupList.substring(i + 1, ShowupList.length()));  //每次迴圈把字串往後遞減一格來選取，並顯示到最後一個字
  //   lcd.print(" ");
  //   delay(500);
  // }

  // for (int i = 0; i <= ShowupList.length(); i++) {
  //   lcd.setCursor(0, 1);
  //   lcd.print(ShowupList.substring(i + 1, ShowupList.length()));  //每次迴圈把字串往後遞減一格來選取，並顯示到最後一個字
  //   lcd.print(" ");
  //   delay(500);
  // }

  // 如果有人不應該來在位置上，而且還投票 蜂鳴器就會響
  if (P1Showup == 0 && resistor1 < 600) {
    if (P1AgreeBtnSt==1 || P1DisagreeBtnSt ==1) {
      digitalWrite(BuzzerPin,HIGH);
      digitalWrite(BuzzerPin,LOW);
      delay(500);

      Alarm += P1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(Alarm);
      lcd.setCursor(0,1);
      lcd.print(Alarm2);
      for (int i=0; i<=5; i++) {
        lcd.display();
        delay(500);
        lcd.noDisplay();
        delay(500);
      }
      delay(3000);

    }
  }
  if (P2Showup == 0 && resistor2 < 600) {
    if (P2AgreeBtnSt==1 || P2DisagreeBtnSt ==1) {
      digitalWrite(BuzzerPin,HIGH);
      digitalWrite(BuzzerPin,LOW);
      delay(500);

      Alarm += P2;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(Alarm);
      lcd.setCursor(0,1);
      lcd.print(Alarm2);

      for (int i=0; i<=5; i++) {
        lcd.display();
        delay(500);
        lcd.noDisplay();
        delay(500);
      }
      delay(3000);
    }
  }
  if (P3Showup == 0 && resistor3 < 600) {
    if (P3AgreeBtnSt==1 || P3DisagreeBtnSt ==1) {
      Serial.println("INININ");
      digitalWrite(BuzzerPin,HIGH);
      delay(1000);
      digitalWrite(BuzzerPin,LOW);

      Alarm += P1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(Alarm);
      lcd.setCursor(0,1);
      lcd.print(Alarm2);


      for (int i=0; i<=5; i++) {
        lcd.display();
        delay(500);
        lcd.noDisplay();
        delay(500);
      }
      delay(3000);
    }
  }

  Serial.println(resistor3);
  delay(500);
}