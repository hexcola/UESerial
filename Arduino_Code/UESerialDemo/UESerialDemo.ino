#include <Servo.h>

Servo myServo;
int servoPin = 9;
int currentAngle;

String inputBuffer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    inputBuffer = Serial.readString();
    ProcessSignalData(inputBuffer);
  }
}

void ProcessSignalData(String signalData)
{
  //if(signalData != 
  int speratorIndex = signalData.indexOf('_');
  
  // get the Signal
  int signal = signalData.substring(0,speratorIndex).toInt();
  
  // get the data
  int data = signalData.substring(speratorIndex + 1).toInt();
  
  
  // do something here
  // my example is 
  if(!myServo.attached())
  {
    myServo.attach(servoPin);
  }
  
  if(myServo.attached() && myServo.read() != data)
  { 
    myServo.write(data);
    delay(500);
  }
}
