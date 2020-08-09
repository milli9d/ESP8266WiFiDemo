// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 02 - ESP8266 WiFi Modes Demo + OTA Demo
#include "WiFi_MS.h"

#define MULTI                       //uncomment for WiFi_multiAP

#ifndef WIFI_SSID
  #define WIFI_SSID "Boom Nation 2G"
  #define WIFI_PASS "boomboomboom"
#endif

#ifdef MULTI
  #define AP_NUM 3
  ESP8266WiFiMulti wifiMulti;
  const char* multi_SSID[AP_NUM] = {"Boom Nation 2G", "Boom Nation", "Boom Nation 1"};
#endif

/*
    Connect to WiFi , display debug
*/
void connectWiFi() {
// Note begin time  
  unsigned long beginTime = millis();
  
  // Code for multiple AP ESP8266
#ifdef MULTI
//  Add all access points , addAP(SSID,PASS) const char
  for (int i = 0 ; i < AP_NUM ; i++) {
    wifiMulti.addAP(multi_SSID[i], WIFI_PASS);
  }
  Serial.println("WiFi Multiple AP Connection Attempt!");
//  See which network has best RSSI and connect to it
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
#endif

// Code for single AP mode
#ifndef MULTI
  //  begin takes SSID and KEY as parameters
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  // Display intended WiFi_SSID
  Serial.println("Begin Connecting to " + String(WiFi.SSID()));
  // The WiFi takes time to establish connection so we wait untill connection is established
  // WiFi.status gives us current status ,
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
#endif

// Display Debug Message
  float timeElapsed = (float(millis()) - float(beginTime)) / 1000;
  Serial.println("\nConnected to " + String(WiFi.SSID()) + "\nTook " + String(timeElapsed) + " seconds to connect.");

//===========================================================================================================================
}

/*
   Start here
*/
void setup() {
  //  Begin Serial port 9600 baud
  Serial.begin(9600);
  // New Line to skip gibberish at the begin of sketch on Serial monitor
  Serial.println();

  scanSync();
  scanAsync();
  scanAsyncShort();
  connectWiFi();                      //  See function defintion above

}

void loop() {
  // Nothing
}
