int test_pin1 = 2;
int test_pin2 = 4;
int test_pin3 = 5;
int test_pin4 = 15;
int test_pin5 = 17;
int test_pin6 = 18;
int test_pin7 = 19;
int test_pin8 = 23; // cannot work

void setup() {
  // put your setup code here, to run once:
pinMode(test_pin1, OUTPUT);
pinMode(test_pin2, OUTPUT);
pinMode(test_pin3, OUTPUT);
pinMode(test_pin4, OUTPUT);
pinMode(test_pin5, OUTPUT);
pinMode(test_pin6, OUTPUT);
pinMode(test_pin7, OUTPUT);
pinMode(test_pin8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(test_pin1, HIGH);
digitalWrite(test_pin2, HIGH);
digitalWrite(test_pin3, HIGH);
digitalWrite(test_pin4, HIGH);
digitalWrite(test_pin5, HIGH);
digitalWrite(test_pin6, HIGH);
digitalWrite(test_pin7, HIGH);
digitalWrite(test_pin8, HIGH);

delay(500);

digitalWrite(test_pin1, LOW);
digitalWrite(test_pin2, LOW);
digitalWrite(test_pin3, LOW);
digitalWrite(test_pin4, LOW);
digitalWrite(test_pin5, LOW);
digitalWrite(test_pin6, LOW);
digitalWrite(test_pin7, LOW);
digitalWrite(test_pin8, LOW);

delay(500);
}
