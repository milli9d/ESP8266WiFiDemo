#pragma once
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "pages.h"

// Hardware Config ===============================================
// Hardware Pins
#define DHTTYPE DHT22
#define DHTPIN 5
#define LED 15
#define LED2 LED_BUILTIN

#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4
// Wifi Params
#define WIFI_SSID "Boom Nation 2G"
#define WIFI_PASS "boomboomboom"
// Initialize Objects

static ESP8266WebServer server(80);
static DHT dht(DHTPIN, DHTTYPE);
static WiFiClient client;
static Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

//================================================================

// MISC Declarations =========================================
#define hline Serial.println("======================================================================================");
static const char* facturl PROGMEM =  "http://numbersapi.com/random";
static const char* insulturl PROGMEM =  "http://evilinsult.com/generate_insult.php?lang=en&type=text";
static const char* quoteurl PROGMEM =  "http://api.forismatic.com/api/1.0/?method=getQuote&format=text&lang=en";
static const char* timeurl PROGMEM =  "http://worldtimeapi.org/api/ip.txt";


// Function Declarations =========================================

// WiFi Functionalities ++++++++++++++++++++++++++++++++++++
//Scan all networks available and display on Serial monitor
void SSID_Scan();
//Connect to network (WIFI_SSID,WIFI_PASS)
void WiFiConnect();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Server Functionalities ++++++++++++++++++++++++++++++++++
// Start ESP Server and configure links
void mainServer();
void rootHandle();
void LEDHandle();
void LED2Handle();
String genDHT();
void DHTHandle();
void QHandle();
void clrHandle();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// TFT Functionalities +++++++++++++++++++++++++++++++++++++
void tft_setup();
void drawText(char *text, uint16_t color);
void drawTextln(char *text, uint16_t color);
void clrScr();
void serverStatus();
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//================================================================


//Scan all networks available and display on Serial monitor
void SSID_Scan() {
  //  Set to station mode (node)
  WiFi.mode(WIFI_STA);
  //  Delete older scan entries
  WiFi.scanDelete();
  //  Disconnect just in case
  WiFi.disconnect();
  //  Give time to disconnect
  delay(100);
  //  Scan for networks , the function returns number of networks found , results
  //  are stored in MCU memory
  int num = WiFi.scanNetworks();
  tft.printf("\n%d network(s) found\n", num);
  for (int i = 0 ; i < num ; i++) {
    //  Access each network entry as an array
    tft.printf("%d: %s\nRSSI: %d dB\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
  delay(2000);
}

//Connect to network (WIFI_SSID,WIFI_PASS)
void WiFiConnect() {
  // Connect to given SSID and PASS , by default will reconnect if connection lost
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  // Change to false to disable auto-connect (Optional Command)
  WiFi.setAutoConnect(true);

  // SET ESP8266 network name (hostname) to the parameter given
  WiFi.hostname("Milind_ESP8266");
  // Give no parameter to GET hostname
  clrScr();
  tft.setTextSize(2);
  tft.println(WiFi.hostname());
  tft.setTextSize(1);
  tft.println("Connecting to Wi-Fi");
  tft.println(WIFI_SSID);
  //Wait till WiFi status is WL_CONNECTED , if anything else , go inside loop
  while (WiFi.status() != WL_CONNECTED)
  {
    // Wait sometime for status to change , ESP8266 attempts reconnection all the time
    delay(500);
    tft.print(".");
  }
  tft.printf("\n\n\n");
  tft.println("STATUS : Connected ");
  // Command gives local network IP
  tft.println(WiFi.localIP());

  delay(2000);
}
