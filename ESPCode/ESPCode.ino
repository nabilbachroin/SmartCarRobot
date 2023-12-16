#include <Arduino.h>
#include <Bonezegei_DHT11.h>

const int trigPin1 = 12; 
const int echoPin1 = 13;
const int trigPin2 = 27;
const int echoPin2 = 14;
const int trigPin3 = 26; 
const int echoPin3 = 25; 
const int trigPin4 = 33; 
const int echoPin4 = 32;

const int ledInd = 22;
Bonezegei_DHT11 dht(21);
float tempDeg = 0;

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2;
  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(ledInd, OUTPUT);

  dht.begin();
  digitalWrite(ledInd, 1); delay(3000);
  digitalWrite(ledInd, 0);
}

void loop() {
  int BottomDistance_L = getDistance(trigPin1, echoPin1);
  int BottomDistance_R = getDistance(trigPin2, echoPin2);
  int TopDistance_L = getDistance(trigPin3, echoPin3);
  int TopDistance_R = getDistance(trigPin4, echoPin4);

  if((BottomDistance_L < 3 || BottomDistance_L > 4) || (BottomDistance_R < 2 || BottomDistance_R > 4) ||
     (TopDistance_L < 13) || (TopDistance_R < 13))
     {
        //digitalWrite(ledInd, 1);
     }
  else
     {
        //digitalWrite(ledInd, 0);
     }

  if (dht.getData()) {
    tempDeg = dht.getTemperature();
    Serial.printf("Temperature: %0.1lf°C ", tempDeg);
    Serial.println();
  }

    if (tempDeg > 30) {
      digitalWrite(ledInd, 1);
    } else {
      digitalWrite(ledInd, 0);
    }

  Serial.print("BottomDistance_L: ");
  Serial.print(BottomDistance_L);
  Serial.println(" cm");

  Serial.print("BottomDistance_R: ");
  Serial.print(BottomDistance_R);
  Serial.println(" cm");

  Serial.print("TopDistance_L: ");
  Serial.print(TopDistance_L);
  Serial.println(" cm");

  Serial.print("TopDistance_R: ");
  Serial.print(TopDistance_R);
  Serial.println(" cm");

  delay(333);
}
