#include <Servo.h>

const int motorpin = 5;
Servo motor;
 
const int motorPin1 = 6;
const int motorPin2 = 5;
const int speedPin = 10;

const int sensorPin = A0;

// All dimensions in centimeters
const double diam = 5.5;
const double desiredDist = 100.0;
const double stoppingDelay = 1;

void setup()
{
  motor.attach(motorpin);

  Serial.begin(9600);

  // 91 is stop
  motor.write(120);
}
 
const int lowerThres = 100;
int count = 0;
int pR = lowerThres + 1;
 
 
int stopped = 0;
long time_prev;
double running_speed = 0;
 
void loop()
{ 
  if(stopped)
    return;
 
  int r = analogRead(sensorPin);
 
  if(r > lowerThres && pR < lowerThres)
  {
    double speed = (PI * diam / 4.0) / double(time_prev-millis());
    running_speed = (running_speed + speed)/2.0;
    count++;
    time_prev = millis();
  }
  Serial.println(r);
  //Serial.println(running_speed * 1000);
 
  pR = r;
 
  if(((double)(count + 1)/ 4.0f) * PI * diam > desiredDist - stoppingDelay * running_speed)
  //(count + 1 >= 200)
  {
    //digitalWrite(motorPin1, LOW);
    //digitalWrite(motorPin2, LOW);
    //analogWrite(speedPin, 0);

    motor.write(91);
 
    stopped = 1;
  }
 
}

