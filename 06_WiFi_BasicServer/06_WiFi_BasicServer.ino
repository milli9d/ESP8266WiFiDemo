// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 06 - ESP8266 Basic Server

// Include Custom libraries
#include "config.h"
#include "WiFi_MS.h"

/*
   Start here
*/
void setup() {
  //  Begin Serial port 9600 baud
  Serial.begin(9600);
  // New Line to skip gibberish at the begin of sketch on Serial monitor
  Serial.println();
  // Red LED on ESP8266 Feather Huzzah
  pinMode(OTA_LED, OUTPUT);

  long unsigned beginInit = millis();             //Note Sketch start time

  initTFT();
  tft.setTextColor(ST77XX_GREEN);
  tft.println("INITIALIZING SYSTEM");
  tft.setTextColor(ST77XX_WHITE);

  connectWiFi();
  enableOTA();

  float initTime = (float(millis()) - beginInit) / 1000;    // Calculate Boot Time

  tft.println("INITIALIZED: " + String(initTime) + " s");   // Report Boot Time

  delay(5000);                                              // Boot Message Window
  welcomeScreen();                                          // Draw ESP Welcome Screen
}

void loop() {

  OTAHandler();                                             // Non-Blocking : Can work concurrently with other code in loop
  sketchTimerHandle();                                      // Non Blocking , can be disabled from config.h , auto-disabled when OTA ON
  

}
