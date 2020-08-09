#pragma once
#include "ESP_MS.h"

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
  Serial.printf("%d network(s) found\n", num);
  for (int i = 0 ; i < num ; i++) {
    //  Access each network entry as an array
    Serial.printf("%d: %s , RSSI: %d dB\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
}


//Connect to network (WIFI_SSID,WIFI_PASS)
void WiFiConnect() {
  // Connect to given SSID and PASS , by default will reconnect if connection lost
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  // Change to false to disable auto-connect (Optional Command)
  WiFi.setAutoConnect(true);
  // Print Debug messages
  Serial.println();
  Serial.print("Connecting to Wi-Fi : ");
  Serial.println(WIFI_SSID);
  //Wait till WiFi status is WL_CONNECTED , if anything else , go inside loop
  while (WiFi.status() != WL_CONNECTED)
  {
    // Wait sometime for status to change , ESP8266 attempts reconnection all the time
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected : ");
  // Command gives local network IP
  Serial.println(WiFi.localIP());
  // SET ESP8266 network name (hostname) to the parameter given
  WiFi.hostname("Milind_ESP8266");
  // Give no parameter to GET hostname
  Serial.println(WiFi.hostname());
}
