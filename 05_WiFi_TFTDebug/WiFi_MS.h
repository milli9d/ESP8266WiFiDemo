#pragma once
#include <ESP8266WiFi.h>                               // Include ESP WiFi Library
#include <ESP8266WiFiMulti.h>

//Include TFT Libraries
#include <Adafruit_GFX.h>                              // Core Graphics Library
#include <Adafruit_ST7735.h>                           // ST7735 Driver -1.44" Green Tab 

#ifdef OTA_En
// OTA dependencies
  #include <ESP8266mDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
#endif

static Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS , TFT_DC , TFT_RST);

//Create new WiFi Multi object
#ifdef MULTI
  ESP8266WiFiMulti wifiMulti;
#endif

// Declarations
// TFT Library Functions
void clrTFT();                //  Clear TFT Black
void initTFT();               //  Initialize and Clear TFT

// OTA Library Functions
void OTAHandler();
void enableOTA();

void connectWiFi();
void printAllNetworks(int num);
void scanSync();
void scanAsync();
void scanAsyncShort();
