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

void emergencyProcedure() {
  stop();
  delay(100);
  digitalWrite(fan, 1);
  Serial.println("Fan aktif");
  delay(3000);
  digitalWrite(fan, 0);
}