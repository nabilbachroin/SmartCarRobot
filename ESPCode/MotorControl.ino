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