#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

Servo myServo;  // create a servo object
SoftwareSerial btSerial(3, 4); // RX, TX

const int sensorPin = A1;
const int redLEDPin = 7; 

int sensorValue;
bool lightsPower;

int angle; // variable to hold the angle for the servo motor
int potVal; // variable to read the value from the analog pin

void setup() {
  // put your setup code here, to run once:
  myServo.attach(8); // attaches the servo on pin 9 to the servo object
  Serial.begin(38400); // open a serial connection to your computer
  btSerial.begin(9600); 
  myServo.write(90);

  Serial.println("Enter AT commands:");
  pinMode(redLEDPin,OUTPUT);

  lightsPower = 0;
}

void loop() {
  if (btSerial.available()){  //如果藍牙有傳資料過來
    int i = btSerial.read();  //把讀到的資料丟給i
    Serial.println(i);
    if(i == 1){    //如果是1，亮燈
      Serial.println("Led On");
      digitalWrite(7,HIGH);
    }
    if(i == 2){    //如果是2，熄燈
      Serial.println("Led Off");
      digitalWrite(7,LOW);
    }
  }

  sensorValue = analogRead(sensorPin);
  delay(5);
  // Serial.print("\nsensor Values \t : ");
  // Serial.println(sensorValue);

  if(sensorValue > 500 && lightsPower==1) {
    myServo.write(20);
    digitalWrite(7, LOW);
    lightsPower = 0;
    delay(3000); 
  } else if (sensorValue > 500 && lightsPower==0) {
    myServo.write(180);
    digitalWrite(7, HIGH);
    lightsPower = 1;
    delay(3000); 
  }
  delay(500);

}
