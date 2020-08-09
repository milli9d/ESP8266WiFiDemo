#pragma once
#include "ESP_MS.h"

void tft_setup() {
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  Serial.println(F("Initialized"));
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  tft.setTextSize(1);
  drawText("Initializing System", ST77XX_GREEN);
}

void clrScr(){
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0,0);
  }

void drawText(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void drawTextln(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.println(text);
}
