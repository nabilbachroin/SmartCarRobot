#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Dhika"
#define WIFI_PASSWORD "hellooo8"
#define API_KEY "AIzaSyCWA1NSc2xM4vd03VUERMS69mYw0ZW5Cmk"
#define DATABASE_URL "https://micro-2023-default-rtdb.asia-southeast1.firebasedatabase.app/" 
#define USER_EMAIL "abiel769@gmail.com"
#define USER_PASSWORD "Microsensors123"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long count = 0;

void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // Membaca command kontrol
  if (Firebase.RTDB.getString(&fbdo, "/control_command")) {
    if (fbdo.dataType() == "string") {
      String controlCommand = fbdo.stringData();
      Serial.print("ControlCommand: ");
      Serial.println(controlCommand);
    }
  } else {
    Serial.print("Gagal membaca control_command: ");
    Serial.println(fbdo.errorReason());
  }

  sendToFirebase();

  // Delay singkat sebelum membaca data lagi
  delay(333);
}

void sendToFirebase() {
  int distance = 50;
  float temperature = 33.3;

  if (Firebase.RTDB.setInt(&fbdo, "/distance", distance)) {
  } else {
    Serial.println("Gagal mengirim jarak");
  }

  if (Firebase.RTDB.setFloat(&fbdo, "/temperature", temperature)) {
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

