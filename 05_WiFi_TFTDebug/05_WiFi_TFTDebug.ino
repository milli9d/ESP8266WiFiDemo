// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 05 - ESP8266 Enable Debug messages on TFT
// Include Custom libraries
#include "config.h"
#include "WiFi_MS.h"

float prevTime = 0;
bool displayTimeTFT = true;

/*
 * Draw ESP8266 Welcome Screen
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
   Start here
*/
void setup() {
  //  Begin Serial port 9600 baud
  Serial.begin(9600);
  // New Line to skip gibberish at the begin of sketch on Serial monitor
  Serial.println();
  // Red LED on ESP8266 Feather Huzzah
  pinMode(OTA_LED, OUTPUT);
  
  tft.setTextColor(ST77XX_GREEN);
  tft.println(F("INITIALIZING SYSTEM"));
  tft.setTextColor(ST77XX_WHITE);
  
  long unsigned beginInit = millis();
  
  initTFT();
  
  connectWiFi();
  enableOTA();
  
  float initTime = (float(millis()) - beginInit) / 1000;
  
  tft.println("INITIALIZED: " + String(initTime) + " s");
  delay(1000);
  
  welcomeScreen();
}

void loop() {
  OTAHandler();                       // Non-Blocking : Can work concurrently with other code in loop
  if (displayTimeTFT) {
    float timeSec = float(millis()) / 1000;
    tft.setCursor(0, 120);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(F("Time Elapsed : "));
    tft.setTextColor(ST77XX_WHITE, ST77XX_RED);
    tft.println(timeSec);
    prevTime = timeSec;
  }
}
