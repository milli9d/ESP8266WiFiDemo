#pragma once
//#define MULTI                       //uncomment for WiFi_multiAP

#ifndef WIFI_SSID
  #define WIFI_SSID "Boom Nation 2G"
  #define WIFI_PASS "boomboomboom"
#endif

#ifdef MULTI
  #define AP_NUM 3
  static const char* multi_SSID[AP_NUM] = {"Boom Nation 2G", "Boom Nation", "Boom Nation 1"};
#endif
