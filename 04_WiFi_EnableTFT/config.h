#pragma once
#define MULTI                                     //  Uncomment for WiFi_multiAP
#define OTA_En                                    //  Uncomment to Enable OTA

// Define OTA timers and flags
#ifdef OTA_En
  #define OTA_LED 15
  #define OTAPeriod 60                            // OTA Period in seconds
//  #define OTA_PASS "admin"
  static bool OTAend = false;                     // Flag to control OTA end
  static unsigned long int OTAbegin = 0 ;         // OTA timer
  static unsigned long LEDtimer = 0 ;             // LED blink timer
#endif

#ifndef WIFI_SSID
  #define WIFI_SSID "Boom Nation 2G"              // 
  #define WIFI_PASS "boomboomboom"                // 
#endif

#ifdef MULTI
  #define AP_NUM 3                                // Number of Access Points to add
  static const char* multi_SSID[AP_NUM] ={"Boom Nation 2G", "Boom Nation", "Boom Nation 1"};
#endif
