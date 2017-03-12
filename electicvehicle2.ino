const int motorPin1 = 6;
const int motorPin2 = 5;
const int speedPin = 10;

const int laserPin = 3;

const int sensorPin = A0;

// All dimensions in centimeters
const double diam = 9.8;
const double desiredDist = 1054;

void setup()
{
  Serial.begin(9600);

  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(speedPin, 255);
}

const int lowerThres = 100;
int count = 0;
int pR = lowerThres + 1;

int stopped = 0;

void loop()
{
  if(stopped)
    return;

  int r = analogRead(sensorPin);

  if(r > lowerThres && pR < lowerThres)
    count++;
  
  Serial.println(r);
  
  pR = r;
    
  if(((double)(count + 1)/ 4.0f) * PI * diam > desiredDist)
  //(count + 1 >= 200)
  {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    analogWrite(speedPin, 0);
  
    stopped = 1;
  }
}
