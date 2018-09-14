#include "Arduino.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
HTTPClient http;

// ISR flags that detects whether a switch was pressed
volatile bool status = true;
bool ISR_change = false;
bool ISR_change2 = false;

// Prevent the ISR triggering on a switch bounce
unsigned long prevMillis = millis();
unsigned long prevMillis2 = millis();

//-------------------------------------------------------------------------
// SETUP     SETUP     SETUP     SETUP     SETUP     SETUP     SETUP
//-------------------------------------------------------------------------
void setup() {
  // Serial Window (debugging)
  Serial.begin(9600);
  delay(100);

  WiFiMulti.addAP("wifi_name", "wifipass");

  connectWifi();

  // I2C Two Wire initialisation
  Wire.begin(D2, D1);

  // PCF8574N is 'reverse' logic inasmuch it SINKS current
  // so HIGH is OFF and LOW is ON (will we remember this?)
  // Turn OFF all pins by sending a high byte (1 bit per byte)
  Wire.beginTransmission(0x3C);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(0x38);
  Wire.write(0x00);
  Wire.endTransmission();

  // Interrupt routine (connect INT on PCF8574 to Pin 3 on Arduino)
  pinMode(D3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(D3), ISRoutine, FALLING);
  
  pinMode(D4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(D4), ISRoutine2, FALLING);
  
  Serial.println("Setup complete.");

  ISRoutine();
  
  ISRoutine2();
}

//-------------------------------------------------------------------------
// LOOP      LOOP     LOOP     LOOP     LOOP     LOOP     LOOP     LOOP
//-------------------------------------------------------------------------
void loop() {
  if (ISR_change) {
    ISR_change = false;
    Serial.println("i-1");
    byte fetchedByte = readAndRunFrom(0x3C);
    Serial.println(fetchedByte);

    /*
    // Let's READ the status of the pins on the expander
    byte abc = 0;
    Wire.requestFrom(0x3C, 1, 1);

    if (Wire.available()) {
      abc = Wire.read();
    }
    Serial.println(abc);

    if (abc != 0) {
      printBinary(abc, 8);

      int pin = findPosition(abc);
  
      if (pin > 0) {
        Serial.printf("Pin %d is ON", pin);
        sendRequest(String(pin));
      }
    } else {
      /* interrupt is always triggered twice
       * once for the original signal/keypress, once for the reset internal reset.
       * The second one will hold no data in "abc" that the one to reset the ISR flag
       */
      
    //}
  } else if (ISR_change2) {
    ISR_change2 = false;
    Serial.println("i-2");

    byte fetchedByte = readAndRunFrom(0x38);
    Serial.println(fetchedByte);
/*
    if(fetchedByte != false)
    {
      printBinary(fetchedByte, 8);

      int pin = findPosition(fetchedByte);
  
      if (pin > 0) {
        Serial.printf("Pin %d is ON", pin);
        sendRequest(String(pin));
      }
    } else {
      ISR_change2 = false;
    }
    */
  }
}

byte readAndRunFrom(byte adr) {
  byte abc = 0;
  Wire.requestFrom(adr, 1, 1);

  if (Wire.available()) {
    abc = Wire.read();
  }

  if (abc != 0) {
    return abc;
  }

  return false;
}

//-------------------------------------------------------------------------
// Interrupt Service Routine to set a flag to show something happened
//-------------------------------------------------------------------------
void ISRoutine() {
  if(millis() - prevMillis > 40) {
    ISR_change = true;
    prevMillis = millis();
  }
}
void ISRoutine2() {
  if(millis() - prevMillis2 > 40) {
    ISR_change2 = true;
    prevMillis2 = millis();
  }
}
