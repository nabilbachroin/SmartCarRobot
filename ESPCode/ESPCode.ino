#include <Arduino.h>
#include <WiFi.h>
#include <Bonezegei_DHT11.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "Dhika"
#define WIFI_PASSWORD "hellooo8"
#define API_KEY "AIzaSyCWA1NSc2xM4vd03VUERMS69mYw0ZW5Cmk"
#define DATABASE_URL "https://micro-2023-default-rtdb.asia-southeast1.firebasedatabase.app/" 
#define USER_EMAIL "abiel769@gmail.com"
#define USER_PASSWORD "Microsensors123"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

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

//const int flame_sensor = 34;
//const int ledInd = 3;
const int fan = 19;
const int buzzer = 22;
Bonezegei_DHT11 dht(21);

float tempDeg = 0;
int BottomDistance_L;
int BottomDistance_R;
int TopDistance_L;
int TopDistance_R;
String controlCommand;

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
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();  
  
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10 * 1000;

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(buzzer, OUTPUT);
  //pinMode(ledInd, OUTPUT);

  pinMode(left_motorPin1, OUTPUT);
  pinMode(left_motorPin2, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_motorPin1, OUTPUT);
  pinMode(right_motorPin2, OUTPUT);
  pinMode(right_pwm, OUTPUT);

  pinMode(fan, OUTPUT);

  dht.begin();
  digitalWrite(buzzer, 1); delay(3000);
  digitalWrite(buzzer, 0);
}

void loop() {
  if (Firebase.RTDB.getString(&fbdo, "/control_command")) {
    if (fbdo.dataType() == "string") {
      controlCommand = fbdo.stringData();
      Serial.print("ControlCommand: ");
      Serial.println(controlCommand);
    }
  } else {
    Serial.print("Gagal membaca control_command: ");
    Serial.println(fbdo.errorReason());
  }

  BottomDistance_L = getDistance(trigPin1, echoPin1);
  BottomDistance_R = getDistance(trigPin2, echoPin2);
  TopDistance_L = getDistance(trigPin3, echoPin3);
  TopDistance_R = getDistance(trigPin4, echoPin4);

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
      //digitalWrite(ledInd, 1);
    } else {
      //digitalWrite(ledInd, 0);
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

  sendToFirebase();
  delay(100);
}

void sendToFirebase() {
  int distance = 50;

  if (Firebase.RTDB.setInt(&fbdo, "/BottomDistance_L", BottomDistance_L)) {
  } else {
    Serial.println("Gagal mengirim jarak1");
  }
  if (Firebase.RTDB.setInt(&fbdo, "/BottomDistance_R", BottomDistance_R)) {
  } else {
    Serial.println("Gagal mengirim jarak2");
  }
  if (Firebase.RTDB.setInt(&fbdo, "/TopDistance_L", TopDistance_L)) {
  } else {
    Serial.println("Gagal mengirim jarak3");
  }
  if (Firebase.RTDB.setInt(&fbdo, "/TopDistance_R", TopDistance_R)) {
  } else {
    Serial.println("Gagal mengirim jarak4");
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/temperature", tempDeg)) {
  } else {
    Serial.println("Gagal mengirim suhu");
  }
}


void token_status_callback(TokenInfo info){
  switch (info.status){
    case token_status_error:
      Serial.println("Token status: Error");
      break;
    case token_status_ready:
      Serial.println("Token status: Ready");
      break;
    default:
      Serial.print("Token status: Unknown - ");
      Serial.println(info.status);
      break;
  }
}