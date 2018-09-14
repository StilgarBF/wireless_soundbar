void sendRequest(String target) {
  if((WiFiMulti.run() == WL_CONNECTED)) {
    Serial.println("[HTTP] GET...");

    // configure target server and url
    String targetUrl = "https://soundpi:3000/sound/" + target;
    String sslFingerPrint = "72 92 28 DF CA 04 59 DA 47 44 1B 06 44 66 A0 D1 D7 BC 2C A8";
    http.begin(targetUrl, sslFingerPrint);

    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been sent and server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println("- Response: --------------");
            Serial.println(payload);
            Serial.println("--------------------------");
        }
    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

  } else {
    Serial.println('connection lost');
    connectWifi();
  }
}
