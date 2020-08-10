#pragma once

#include <ESP8266WiFi.h>                               // Include ESP WiFi Library
#include <ESP8266WiFiMulti.h>

//Include TFT Libraries
#include <Adafruit_GFX.h>                              // Core Graphics Library
#include <Adafruit_ST7735.h>                           // ST7735 Driver -1.44" Green Tab 

// OTA dependencies
#ifdef OTA_En
  #include <ESP8266mDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
#endif

// TFT Screen Object , static to make it static in memory (i.e only be defined once and stays there for all files)
static Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS , TFT_DC , TFT_RST);

//Create new WiFi Multi object
#ifdef MULTI
  ESP8266WiFiMulti wifiMulti;
#endif

// Member Variables (Do Not Delete)
float prevTime = 0;
bool displayTimeTFT = true;


// Declarations =====================================================================================

// TFT Library Functions TFT_func.ino
void welcomeScreen();
void checkCursor(int yPos);
void clrTFT();                //  Clear TFT Black
void initTFT();               //  Initialize and Clear TFT

// OTA Library Functions WIFI_func.ino
void OTAHandler();
void enableOTA();

// WiFi Library Functions WiFi_func.ino
void sketchTimerHandle();
void connectWiFi();
void printAllNetworks(int num);
void scanSync();
void scanAsync();
void scanAsyncShort();
