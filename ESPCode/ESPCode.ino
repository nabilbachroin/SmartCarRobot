#include <Arduino.h>

const int trigPin1 = 12; 
const int echoPin1 = 13;
// const int trigPin2 = ;
// const int echoPin2 = ;
// const int trigPin3 = ; 
// const int echoPin3 = ; 
// const int trigPin4 = ; 
// const int echoPin4 = ;

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
  // pinMode(trigPin2, OUTPUT);
  // pinMode(echoPin2, INPUT);
  // pinMode(trigPin3, OUTPUT);
  // pinMode(echoPin3, INPUT);
  // pinMode(trigPin4, OUTPUT);
  // pinMode(echoPin4, INPUT);
}

void loop() {
  float BottomDistance_L = getDistance(trigPin1, echoPin1);
  //float distance2 = getDistance(trigPin2, echoPin2);
  //float distance3 = getDistance(trigPin3, echoPin3);
  //float distance4 = getDistance(trigPin4, echoPin4);

  Serial.print("Jarak Sensor 1: ");
  Serial.print(BottomDistance_L);
  Serial.println(" cm");

  // Serial.print("Jarak Sensor 2: ");
  // Serial.print(distance2);
  // Serial.println(" cm");

  // Serial.print("Jarak Sensor 3: ");
  // Serial.print(distance3);
  // Serial.println(" cm");

  // Serial.print("Jarak Sensor 4: ");
  // Serial.print(distance4);
  // Serial.println(" cm");

  delay(1000);
}
