const int flame_sensor = 34;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(flame_sensor); // Baca nilai analog dari sensor api
  Serial.print("Sensor Api: ");
  Serial.println(sensorValue);
  delay(333);
}
