#include <Servo.h>

#define E  2.7182818284590452353602874713527f

const int motorpin = 5;
Servo motor;

const int buttonpin = 2;

const int sensorPin = A0;

// All dimensions in centimeters
const double diam = 7.87404;
const double desiredDist = 200.0;

const double stopBefore = 2.0; // distance

const int stopMVel = 91;
const int startMVel = 100;
const int maxMVel = 114;

const int lowerThres = 50;

const double firstOffset = 60.0;
const double secondOffset = 60.0;

void setup()
{
  pinMode(buttonpin, INPUT);
  
  motor.attach(motorpin);

  Serial.begin(9600);
  
  motor.write(stopMVel);
}

int getVel(double x)
{
  /*double a = 0.5 * (double)desiredDist;
  double c = 100.0;
  double p = (x-a) * (x-a) / c;
  
  double v = (double)(maxMVel - stopMVel) / pow(E, p);

  return (stopMVel + (int)v);*/

  if(x < firstOffset)
    return (double)(maxMVel - startMVel) * (x / firstOffset) + startMVel;
  else if(x > desiredDist - secondOffset)
    return (double)(maxMVel - stopMVel) * ((desiredDist - x) / secondOffset) + stopMVel;
  else
    return maxMVel;
}
 
int count = 0;
int pR = lowerThres + 1;

bool stopped = true;

int pb = -1;

long starttime = -1;

long timeout = 8000;

void loop()
{ 
  int b = digitalRead(buttonpin);

  if(millis() - starttime > timeout && starttime != -1)
  {
    stopped = true;
    starttime = millis();
  }
  else if(b != pb && pb != -1)
  {
    //Serial.println("button");

    delay(800);
    
    stopped = !stopped;

    if(!stopped)
    {
      starttime = millis();
    }
  }

  pb = b;

  if(stopped)
  {
    motor.write(stopMVel);
    return;
  }
  
  int r = analogRead(sensorPin);

  //Serial.println(r);
 
  if(r > lowerThres && pR < lowerThres)
    count++;
  
  pR = r;

  double d = ((double)(count) / 2.0) * PI * diam;

  int v = getVel(d);

  /*Serial.print(d);
  Serial.print("   ");
  Serial.println(v);*/

  //Serial.println(digitalRead(buttonpin));
 
  if(d > (desiredDist - stopBefore))
  {
    motor.write(stopMVel);

    count = 0;
 
    stopped = true;
  }
  else
    motor.write(v);
}

