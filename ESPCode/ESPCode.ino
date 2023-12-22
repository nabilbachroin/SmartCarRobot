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

const int DemoPing_use_movementMotor = 39;
const int speed = 85;

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

const int flame_sensor = 34;
//const int ledInd = 3;
const int fan = 19;
const int ledInd = 22;
Bonezegei_DHT11 dht(21);

float tempDeg = 0;
int BottomDistance_L;
int BottomDistance_R;
int TopDistance_L;
int TopDistance_R;
String controlCommand;
String manualCommand;

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
  pinMode(ledInd, OUTPUT);

  pinMode(left_motorPin1, OUTPUT);
  pinMode(left_motorPin2, OUTPUT);
  pinMode(left_pwm, OUTPUT);
  pinMode(right_motorPin1, OUTPUT);
  pinMode(right_motorPin2, OUTPUT);
  pinMode(right_pwm, OUTPUT);

  pinMode(DemoPing_use_movementMotor, INPUT);
  pinMode(fan, OUTPUT);
  pinMode(flame_sensor, INPUT);

  dht.begin();
  
  digitalWrite(ledInd, 1); digitalWrite(fan, 1); delay(3000);
  digitalWrite(ledInd, 0); digitalWrite(fan, 0);
}

void loop() {
  int trig = digitalRead(DemoPing_use_movementMotor);
  int sensorValue = analogRead(flame_sensor);
  // Serial.print("Fire_anlg="); Serial.println(sensorValue);
  //if(sensorValue < 3500)
  if(sensorValue < 100)
    {
      if(!trig) updateDanger();
      if(sensorValue < 20) {emergencyProcedure(); return;}
      stop(); delay(333);
      int prevsensorValue = sensorValue;
      move(-1, 1, speed-5); delay(175); stop(); delay(33);
      move(-1, 1, speed-5);
      sensorValue = analogRead(flame_sensor);
      if(sensorValue > prevsensorValue) move(1, -1, speed-5);
      while(1)
        {
          sensorValue = analogRead(flame_sensor);
          if(sensorValue < 20) {emergencyProcedure(); break;}
        }
      stop();
    }
  else
    {
      if(!trig) updateSecure();
    }

  if(!trig)
    {
      if (Firebase.RTDB.getString(&fbdo, "/control_command")) {
        if (fbdo.dataType() == "string") {
          controlCommand = fbdo.stringData();
          // Serial.print("ControlCommand: ");
          // Serial.println(controlCommand);
        }
      } else {
        Serial.print("Gagal membaca control_command: ");
        Serial.println(fbdo.errorReason());
      }
    }

  BottomDistance_L = getDistance(trigPin1, echoPin1);
  BottomDistance_R = getDistance(trigPin2, echoPin2);
  TopDistance_L = getDistance(trigPin3, echoPin3);
  TopDistance_R = getDistance(trigPin4, echoPin4);

  if(trig)
    {
      if((BottomDistance_L < 9 || BottomDistance_L > 17) || (BottomDistance_R < 9 || BottomDistance_R > 20) ||
        (TopDistance_L < 20) || (TopDistance_R < 20))
        {
          stop(); delay(500); move(-1, -1, speed-2); delay(150); stop(); delay(33);
          if(TopDistance_R < 20 || (BottomDistance_L < 9 || BottomDistance_L > 17))
            {
              move(-1, 1, speed); delay(400);
              stop(); delay(100);
            }
          else if(TopDistance_L < 20 || (BottomDistance_R < 9 || BottomDistance_R > 20))
            {
              move(1, -1, speed); delay(400);
              stop(); delay(100);
            }
        }
      else
        {
          move(1, 1, speed-5);
        }
    }

  if(!trig)
    {
      if(controlCommand == "Manual")
        {
          bool idle = false;
          if(TopDistance_R < 20 || TopDistance_L < 20) {stop(); idle=true;}
          else idle=false;
          if (Firebase.RTDB.getString(&fbdo, "/manual_command")) 
            {
              if (fbdo.dataType() == "string") 
                {
                  manualCommand = fbdo.stringData();
                  // Serial.print("manualCommand: ");
                  // Serial.println(manualCommand);
                }
              if(manualCommand == "left") move(-1, 1, speed);
              else if(manualCommand == "right") move(1, -1, speed);
              else if(manualCommand == "forward" && idle == false) {move(1, 1, speed);}
              else if(manualCommand == "back") move(-1, -1, speed);
              else if(manualCommand == "stop") stop();
            } 
          else 
            {
              Serial.print("Gagal membaca control_command: ");
              Serial.println(fbdo.errorReason());
            }
        }
      else if(controlCommand == "Auto")
        {
          if((BottomDistance_L < 9 || BottomDistance_L > 17) || (BottomDistance_R < 9 || BottomDistance_R > 20) ||
            (TopDistance_L < 20) || (TopDistance_R < 20))
            {
              stop(); delay(500);
              if(TopDistance_R < 20 || (BottomDistance_L < 9 || BottomDistance_L > 17))
                {
                  move(-1, 1, speed); delay(400);
                  stop(); delay(100);
                }
              else if(TopDistance_L < 20 || (BottomDistance_R < 9 || BottomDistance_R > 20))
                {
                  move(1, -1, speed); delay(400);
                  stop(); delay(100);
                }
            }
          else
            {
              move(1, 1, speed);
            }
        }
    }


  if(!trig)
    {
      if (dht.getData()) {
        tempDeg = dht.getTemperature();
        // Serial.printf("Temperature: %0.1lf°C ", tempDeg);
        // Serial.println();
      }

      if (tempDeg > 30) {
          digitalWrite(ledInd, 1);
        } else {
          digitalWrite(ledInd, 0);
        }
    }

  // Serial.print("BottomDistance_L: ");
  // Serial.print(BottomDistance_L);
  // Serial.println(" cm");

  // Serial.print("BottomDistance_R: ");
  // Serial.print(BottomDistance_R);
  // Serial.println(" cm");

  // Serial.print("TopDistance_L: ");
  // Serial.print(TopDistance_L);
  // Serial.println(" cm");

  // Serial.print("TopDistance_R: ");
  // Serial.print(TopDistance_R);
  // Serial.println(" cm");

  if(!trig) sendToFirebase();
  delay(33);
}
