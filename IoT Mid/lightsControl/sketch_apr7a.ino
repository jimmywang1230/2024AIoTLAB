#include <Servo.h>
#include <stdbool.h>
#include <SoftwareSerial.h>

Servo myServo;  // create a servo object
SoftwareSerial BTSerial(9, 10);

const int sensorPin = A1;
const int redLEDPin = 7; 

int sensorValue;
bool lightsPower;

int angle; // variable to hold the angle for the servo motor
int potVal; // variable to read the value from the analog pin

void setup() {
  // put your setup code here, to run once:
  myServo.attach(8); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600); // open a serial connection to your computer
  BTSerial.begin(38400); 
  myServo.write(90);

  Serial.println("Enter AT commands:");
  pinMode(redLEDPin,OUTPUT);

  lightsPower = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  // if (BTSerial.available()){Serial.write(BTSerial.read());}
  // if (Serial.available()){BTSerial.write(Serial.read());}

  sensorValue = analogRead(sensorPin);
  delay(5);
  // Serial.print("\nsensor Values \t : ");
  // Serial.println(sensorValue);

  if(sensorValue > 500 && lightsPower==1) {
    myServo.write(20);
    digitalWrite(7, LOW);
    lightsPower = 0;
  } else if (sensorValue > 500 && lightsPower==0) {
    myServo.write(180);
    digitalWrite(7, HIGH);
    lightsPower = 1;
  }
  delay(3000);

}
