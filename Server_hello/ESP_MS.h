#pragma once
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "pages.h"

#define DHTTYPE DHT22
#define DHTPIN 4

#define WIFI_SSID "Boom Nation 2G"
#define WIFI_PASS "boomboomboom"

void mainServer();

//Scan all networks available and display on Serial monitor
void SSID_Scan();

//Connect to network (WIFI_SSID,WIFI_PASS)
void WiFiConnect();
