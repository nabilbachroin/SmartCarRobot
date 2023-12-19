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

// Motor 1
const int left_motorPin1 = 2;
const int left_motorPin2 = 4;
const int left_pwm = 5; // Speed (PWM)
// Motor 2
const int right_motorPin1 = 15;
const int right_motorPin2 = 17;
const int right_pwm = 18; // Speed (PWM)

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

  pinMode(left_motorPin1, OUTPUT);
  pinMode(left_motorPin2, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_motorPin1, OUTPUT);
  pinMode(right_motorPin2, OUTPUT);
  pinMode(right_pwm, OUTPUT);

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
        stop(); delay(500);

        if((TopDistance_L < 13) || (TopDistance_R < 13))
          {
            if(TopDistance_L < 13)
              {
                move(-1, 1, 33); delay(500);
                stop();
                /* check flame
                if(flame == 1)
                  {
                    digitalWrite(fan, 1);
                    move(-1, 1, 133); delay(333);
                    move(1, -1, 133); delay(666);
                    move(-1, 1, 133); delay(333);
                    stop();
                    digitalWrite(fan, 0);
                  }
                */
              }
            else
              {
                move(1, -1, 33); delay(500);
                stop();
                /* check flame
                if(flame == 1)
                  {
                    digitalWrite(fan, 1);
                    move(-1, 1, 133); delay(333);
                    move(1, -1, 133); delay(666);
                    move(-1, 1, 133); delay(333);
                    stop();
                    digitalWrite(fan, 0);
                  }
                */
              }
          }

        move(-1, -1, 200); delay(500);
        move(-1, 1, 175); delay(500);
        stop(); delay(333);
     }
  else
     {
        move(1, 1, 50);
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
