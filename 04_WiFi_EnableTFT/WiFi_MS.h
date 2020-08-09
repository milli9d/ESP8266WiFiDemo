#pragma once
#include <ESP8266WiFi.h>                               // Include ESP WiFi Library
#include <ESP8266WiFiMulti.h>

#ifdef OTA_En
// OTA dependencies
  #include <ESP8266mDNS.h>
  #include <WiFiUdp.h>
  #include <ArduinoOTA.h>
#endif


// Declarations
void OTAHandler();
void enableOTA();
void connectWiFi();
void printAllNetworks(int num);
void scanSync();
void scanAsync();
void scanAsyncShort();
