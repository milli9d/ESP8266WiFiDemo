// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 03 - ESP8266 Enable OTA

// Include Custom libraries
#include "config.h"
#include "WiFi_MS.h"

// OTA dependencies
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define OTA_En                                    //Uncomment to Enable OTA

// Define OTA timers and flags
#ifdef OTA_En
// OTA Enabled Period (Seconds)
  #define OTAPeriod 60
//  #define OTA_PASS "admin"
  static bool OTAend = false;
  static unsigned long int OTAbegin = 0 ;
  static unsigned long LEDtimer = 0 ;
#endif

// Configure OTA Handles and Enable OTA
void enableOTA() {
#ifdef OTA_En
  
  // Set OTA host name and Password for security
  ArduinoOTA.setHostname("Milind_ESP8266");
  
  #ifdef OTA_PASS
    ArduinoOTA.setPassword(OTA_PASS);
  #endif
  
  // OTA Handles(Optional) - These define behaviour on state changes , ESP8266 can perform tasks while OTA happens in background
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate Complete Restarting");
    ESP.restart();
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    if (millis() - LEDtimer > 10 && !OTAend ) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      LEDtimer = millis();
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  //  This command turns on OTA mode , OTA mode only runs till the OTAHandle() runs inside a loop , so put it inside void loop
  ArduinoOTA.begin();
  Serial.println("OTA On for " + String(OTAPeriod) + " seconds."  );
#endif
}

/*
   Start here
*/
void setup() {
  //  Begin Serial port 9600 baud
  Serial.begin(9600);
  // New Line to skip gibberish at the begin of sketch on Serial monitor
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);

  connectWiFi();                      //  Connect to WiFi as configured in config.h
  enableOTA();                        // See function body , also see void loop()
}

void loop() {
  
#ifdef OTA_En
// If OTA Period has ended set flag = true and print message
  if (millis() - OTAbegin > OTAPeriod * 1000 && OTAend == false) {
    OTAend = true;
    Serial.println("OTA Period Ended");
  }
// Run OTA handler
  if (!OTAend) {
    // Run the OTA handler
    ArduinoOTA.handle();
  }
/* ESP can do other stuff while OTA is enabled and running
   Here we use a LED indicator to tell us when OTA mode is enabled
   This part of code will auto disable after OTAPeriod ends
*/
  if (millis() - LEDtimer > 100 && !OTAend ) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    LEDtimer = millis();
  }
#endif

}
