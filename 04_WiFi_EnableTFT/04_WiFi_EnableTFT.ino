// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 04 - ESP8266 Enable ST7735 TFT Screen connected on Default SPI bus
// Include Custom libraries
#include "config.h"
#include "WiFi_MS.h"

//Include TFT Libraries
#include <Adafruit_GFX.h>           // Core Graphics Library
#include <Adafruit_ST7735.h>        // ST7735 Driver -1.44" Green Tab 


#ifndef TFT_CS
#define TFT_CS         2
#define TFT_RST        16
#define TFT_DC         0
#endif

float prevTime = 0;
bool displayTime ;

static Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS , TFT_DC , TFT_RST);

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

  connectWiFi();
  enableOTA();

  Serial.println(F("ST77xx TFT Begin"));
  tft.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
  Serial.println(F("TFT Initialized"));

  tft.setTextWrap(true);

  // Draw a Welcome Screen
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(ST77XX_RED);
  tft.println(F("ESP8266\nWiFi"));
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.fillRect(0, tft.getCursorY() + 10, 140, 70, ST77XX_RED );
  tft.println(F("\n\nConnected : "));
  tft.print(WiFi.SSID());
  tft.println();
  displayTime = true;
}

void loop() {
  OTAHandler();                       // Non-Blocking : Can work concurrently with other code in loop
  if (displayTime) {
    float timeSec = float(millis()) / 1000;
    tft.setCursor(0, 120);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(F("Time Elapsed : "));
    tft.setTextColor(ST77XX_WHITE, ST77XX_RED);
    tft.println(timeSec);
    prevTime = timeSec;
  }
}
