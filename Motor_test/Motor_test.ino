#include <Arduino.h>

int speed;

// Motor 1
const int left_motorPin1 = 2;
const int left_motorPin2 = 4;
const int left_pwm = 5; // Speed (PWM)
// Motor 2
const int right_motorPin1 = 15;
const int right_motorPin2 = 17;
const int right_pwm = 18; // Speed (PWM)

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(left_motorPin1, OUTPUT);
pinMode(left_motorPin2, OUTPUT);
pinMode(left_pwm, OUTPUT);
pinMode(right_motorPin1, OUTPUT);
pinMode(right_motorPin2, OUTPUT);
pinMode(right_pwm, OUTPUT);
}

void loop() {
// speed = 33;  // not moving
// speed = 40;  // not moving
// speed = 50;  // not moving

// speed = 85;  // 
// Serial.println(speed);
// move(-1, 1, speed); delay(3000); stop(); delay(500);
// move(1, -1, speed); delay(3000); stop(); delay(500);
// move(1, 1, speed); delay(3000); stop(); delay(500);
// move(-1, -1, speed); delay(3000); stop(); delay(500);

// speed = 100;  // ok
// Serial.println(speed);
// move(-1, 1, speed); delay(3000); stop(); delay(500);
// move(1, -1, speed); delay(3000); stop(); delay(500);
// move(1, 1, speed); delay(3000); stop(); delay(500);
// move(-1, -1, speed); delay(3000); stop(); delay(500);

// speed = 150;  // ok
// Serial.println(speed);
// move(-1, 1, speed); delay(3000); stop(); delay(500);
// move(1, -1, speed); delay(3000); stop(); delay(500);
// move(1, 1, speed); delay(3000); stop(); delay(500);
// move(-1, -1, speed); delay(3000); stop(); delay(500);

speed = 200;  // ok
Serial.println(speed);
move(-1, 1, speed); delay(3000); stop(); delay(5000);
move(1, -1, speed); delay(3000); stop(); delay(5000);
move(1, 1, speed); delay(3000); stop(); delay(5000);
move(-1, -1, speed); delay(3000); stop(); delay(5000);

}


void stop()
  {
    digitalWrite(left_motorPin1, LOW);
    digitalWrite(left_motorPin2, LOW);
    digitalWrite(right_motorPin1, LOW);
    digitalWrite(right_motorPin2, LOW);
  }

void move(int left, int right, int speed)
  {
    if(left > 0)
      {
        digitalWrite(left_motorPin1, HIGH);
        digitalWrite(left_motorPin2, LOW);
      }
    else if(left < 0)
      {
        digitalWrite(left_motorPin1, LOW);
        digitalWrite(left_motorPin2, HIGH);
      }
    
    if(right > 0)
      {
        digitalWrite(right_motorPin1, LOW);
        digitalWrite(right_motorPin2, HIGH);
      }
    else if(right < 0)
      {
        digitalWrite(right_motorPin1, HIGH);
        digitalWrite(right_motorPin2, LOW);
      }

    analogWrite(left_pwm, speed);
    analogWrite(right_pwm, speed);
  }