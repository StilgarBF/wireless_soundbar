void connectWifi() {
  Serial.println("connecting wifi ...");
  WiFiMulti.run();

  unsigned long constart = millis();
  bool connected = false;

  while(
    !connected
    || (millis() - constart < 12000)
  ) {
    delay(1000);
    Serial.println("waiting ...");

    if(WiFiMulti.run() != WL_CONNECTED) {
      connected = true;
    }
  }

  if(connected) {
    Serial.println("... we are connected!");
  } else {
    Serial.println("Unable to connect!");
  }
  
}
