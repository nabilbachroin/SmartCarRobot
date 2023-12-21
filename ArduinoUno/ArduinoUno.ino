const int fanTrig_in = A0;
const int fanTrig_out = 7;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(fanTrig_in, INPUT);
pinMode(fanTrig_out, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(fanTrig_in) == HIGH) {Serial.println("aktif"); digitalWrite(fanTrig_out, HIGH);}
else digitalWrite(fanTrig_out, LOW);

delay(33);
}
