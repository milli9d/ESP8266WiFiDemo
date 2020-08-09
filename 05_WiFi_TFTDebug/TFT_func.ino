#pragma once
#include "WiFi_MS.h"

void clrTFT() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
}

void initTFT() {
  Serial.println(F("ST77xx TFT Begin"));
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  Serial.println(F("TFT Initialized"));
  tft.setTextWrap(true);
  clrTFT();
  
}
