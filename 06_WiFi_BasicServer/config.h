#pragma once

#define MULTI                                       //  Uncomment for WiFi_multiAP
#define OTA_En                                      //  Uncomment to Enable OTA

#ifndef TFT_CS
#define TFT_CS         16
#define TFT_RST        5
#define TFT_DC         4
#endif

#define OTA_LED 2                                  // Comment to disable OTA LED and free pin


// Define OTA timers and flags
#ifdef OTA_En
  #define OTAPeriod 60                              // OTA Period in seconds
//  #define OTA_PASS "admin"
  static bool OTAend = false;                       // Flag to control OTA end
  static unsigned long int OTAbegin = 0 ;           // OTA timer
  static unsigned long LEDtimer = 0 ;               // LED blink timer
#endif

#ifndef WIFI_SSID
  #define WIFI_SSID "Boom Nation 2G"                // 
  #define WIFI_PASS "boomboomboom"                  // 
#endif

#ifdef MULTI
  #define AP_NUM 3                                  // Number of Access Points to add
  static const char* multi_SSID[AP_NUM] ={"Boom Nation 2G", "Boom Nation", "Boom Nation 1"};
#endif
