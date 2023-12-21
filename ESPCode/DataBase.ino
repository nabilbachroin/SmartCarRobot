void sendToFirebase() {
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

void updateDanger() {
  if (Firebase.RTDB.setInt(&fbdo, "/Fire", 1)) {
  } else {
    Serial.println("Gagal mengirim jarak1");
  }
}

void updateSecure() {
  if (Firebase.RTDB.setSInt(&fbdo, "/Fire", 0)) {
  } else {
    Serial.println("Gagal mengirim jarak1");
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