#pragma once
#include <ESP8266WiFi.h>                               // Include ESP WiFi Library
#include <ESP8266WiFiMulti.h>

// Declarations
void printAllNetworks(int num);
void scanSync();
void scanAsync();
void scanAsyncShort();
