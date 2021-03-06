// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 05 - ESP8266 Enable Debug messages on TFT


// Include Custom libraries
#include "config.h"
#include "WiFi_MS.h"

float prevTime = 0;
bool displayTimeTFT = true;

/*
   Draw ESP8266 Welcome Screen
*/
void welcomeScreen() {
  clrTFT();
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_RED);
  tft.println(F("ESP8266\nWiFi"));
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.fillRect(0, tft.getCursorY() + 10, 140, 70, ST77XX_RED );
  tft.println(F("\n\nConnected : "));
  tft.print(WiFi.SSID());
  tft.println();
}

/*
   Check cursor and return to beginning if after end
*/
void checkCursor(int yPos) {
  if (tft.getCursorY() > yPos) {
    delay(1000);
    clrTFT();
  }
}


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

  if (displayTimeTFT) {                                     // Find flag in Config.h , set to true to enable Sketch Timer on TFT Screen
    float timeSketchElapsed = float(millis()) / 1000;
    tft.setCursor(0, 120);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(F("Time Elapsed : "));
    tft.setTextColor(ST77XX_WHITE, ST77XX_RED);
    tft.println(timeSketchElapsed);
    prevTime = timeSketchElapsed;
  }

}
