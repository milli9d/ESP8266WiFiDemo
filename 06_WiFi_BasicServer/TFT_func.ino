#pragma once
#include "WiFi_MS.h"

/*
 * Clear TFT and Set Cursor to Start
 */
void clrTFT() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
}

/*
 *  Initialize TFT Driver and print on Serial Debug
 */
void initTFT() {
  Serial.println(F("ST77xx TFT Begin"));
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  Serial.println(F("TFT Initialized"));
  tft.setTextWrap(true);
  clrTFT();
}

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
