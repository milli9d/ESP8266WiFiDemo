#pragma once

#include "config.h"
#include "WiFi_MS.h"

// =================================== Custom Library Definitions ===================


void sketchTimerHandle(){
  
   if (displayTimeTFT) {                                     // Find flag in Config.h , set to true to enable Sketch Timer on TFT Screen
    float timeSketchElapsed = float(millis()) / 1000;
    tft.setCursor(0, 120);
    tft.setTextColor(ST77XX_WHITE);
    tft.print(F("Time Elapsed : "));
    tft.setTextColor(ST77XX_WHITE, ST77XX_RED);
    tft.println(timeSketchElapsed);
    prevTime = timeSketchElapsed;
  }}



/*
   Put inside a loop to start OTA listening , it will work only till this code is running in a loop
*/
void OTAHandler() {
  
#ifdef OTA_En
//  Set DisplaySketchTimer to False
  displayTimeTFT = false;
//  Note OTA Elapsed Time
  unsigned long OTAElapsedTime = millis() - OTAbegin;
  
  // If OTA Period has ended set flag = true and print message
  if (OTAElapsedTime > OTAPeriod * 1000 && OTAend == false) {
    OTAend = true;
    Serial.println("OTA Period Ended");
  // Draw over OTA Timer to remove timer text   
    tft.fillRect(0,120,140,20,ST77XX_RED);
  }

  // Run OTA handler
  if (!OTAend) {
    // Run the OTA handler
    ArduinoOTA.handle();
  }
  
  /* ESP can do other stuff while OTA is enabled and running
     Here we disable the LED indicator to tell us when OTA mode is enabled
     And draw a period indicator on the TFT screen
     This part of code will auto disable after OTAPeriod ends
  */
  if (millis() - LEDtimer > 100 && !OTAend ) {
    #ifdef OTA_LED
      digitalWrite(OTA_LED, !digitalRead(OTA_LED));
    #endif
    LEDtimer = millis();
//    Display OTA Timer
    tft.setCursor(0, 120);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("OTA Enabled : ");
    tft.setTextColor(ST77XX_WHITE, ST77XX_RED);
    tft.println(String((OTAPeriod - (OTAElapsedTime / 1000))) +" sec");
  }

#endif

}

/*
    Configure OTA Handles and Enable OTA
*/

void enableOTA() {
#ifdef OTA_En

  // Set OTA host name and Password for security
  ArduinoOTA.setHostname("Milind_ESP8266");
  #ifdef OTA_PASS
    ArduinoOTA.setPassword(OTA_PASS);
  #endif

  // OTA Handles(Optional) - These define behaviour on state changes , ESP8266 can perform tasks while OTA happens in background
  ArduinoOTA.onStart([]() {
    clrTFT();
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(1);
    tft.println("RECIEVING OTA!");
//    Serial.println("Start updating ");
  });

  ArduinoOTA.onEnd([]() {
//    Serial.println("\nUpdate Complete Restarting");
    tft.println("\nUpdate Complete\nRestarting");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
//    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    if (millis() - LEDtimer > 10 && !OTAend ) {
      tft.setCursor(0,40);
      tft.setTextColor(ST77XX_GREEN,ST77XX_BLACK);
      tft.printf("Progress: %u%%\r", (progress / (total / 100)));
      tft.setTextColor(ST77XX_GREEN);
      #ifdef OTA_LED
        digitalWrite(OTA_LED, !digitalRead(OTA_LED));
      #endif      
      LEDtimer = millis();
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    tft.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      tft.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      tft.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      tft.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      tft.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      tft.println("End Failed");
    }
  });

  //  This command turns on OTA mode , OTA mode only runs till the OTAHandle() runs inside a loop , so put it inside void loop
  ArduinoOTA.begin();
//  Serial.println("OTA On for " + String(OTAPeriod) + " seconds."  );
#endif
}

/*
    Connect to WiFi , display debug
*/
void connectWiFi() {
  checkCursor(50);
//  Set Color Green to Identify Status message
  tft.setTextColor(ST77XX_GREEN);
  
  // Note begin time
  unsigned long beginTime = millis();
  
  // Code for multiple AP ESP8266
#ifdef MULTI
  
  //  Add all access points , addAP(SSID,PASS) const char
  for (int i = 0 ; i < AP_NUM ; i++) {
    wifiMulti.addAP(multi_SSID[i], WIFI_PASS);
  }
  
  Serial.println(F("WiFi(Multi-AP):"));
  tft.println(F("WiFi(Multi-AP):"));
  
  //  See which network has best RSSI and connect to it
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    tft.print(".");
    delay(500);
  }
#endif

  // Code for single AP mode
#ifndef MULTI
  
  //  begin takes SSID and KEY as parameters
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  // Display intended WiFi_SSID
  Serial.print(F("Begin Connecting to "));
  Serial.println(String(WiFi.SSID()));

  tft.println(F("Connect (Single AP): "));
  tft.println(String(WiFi.SSID()));
  
  // The WiFi takes time to establish connection so we wait untill connection is established
  // WiFi.status gives us current status ,
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    tft.print(".");
    delay(500);
  }
#endif

  // Display Debug Message
  float timeElapsed = (float(millis()) - float(beginTime)) / 1000;
  
  Serial.println("\nConnected to " + String(WiFi.SSID()) + "\nTook " + String(timeElapsed) + " seconds to connect.");
  tft.println("\nConnected:\n" + String(WiFi.SSID()) + "\n" + String(timeElapsed) + " seconds.");
  //===========================================================================================================================

}

// Supplementary function to print all networks
void printAllNetworks(int num) {
  //  Set Color Green to Identify Status message
  tft.setTextColor(ST77XX_GREEN);
  //  If no networks are discovered
  if (num <= 0) {
    Serial.println(F("No Networks Found!"));
    tft.println(F("No Networks Found!"));
  }
  //  If networks found , run for loop on number of networks and fetch/print information
  else {
    Serial.println(String(num) + " networks found!");
    tft.println(String(num) + " networks found!");
    for (int i = 0 ; i < num ; i++) {
      Serial.println(String(String(i) + ".SSID = " + String(WiFi.SSID(i)) + " RSSI" + String(WiFi.RSSI(i))));
      checkCursor(120);
      tft.println(String(String(i) + ".SSID = " + String(WiFi.SSID(i)) + ":RSSI(" + String(WiFi.RSSI(i)))+")dB");
      
    }
  }
}

/*  
 * Synchronous WiFi Networks Scan  
 */ 
void scanSync() {
  checkCursor(50);
  //  Set Color Green to Identify Status message
  tft.setTextColor(ST77XX_GREEN);
  
  Serial.println("\n\nSync(Blocking)Scan!");
  tft.println(F("\n\nSync(Blocking)Scan!"));
  // Store time of execution when scan begins
  unsigned long scanBegin =  millis();
  
  /* Scan for WiFi networks in range and store in memory
     WiFi.scanNetworks(<?async>, <?show_hidden>) - boolean flags
     Returns number of networks found , store in int
     This function is blocking , will take 100s of millis to complete */
  int WIFI_FOUND = WiFi.scanNetworks();
  // Get the time elapsed during scan
  unsigned long scanEnd = millis() - scanBegin;

  // Time is in milliseconds , convert to seconds
  float scanTimeSec = float(scanEnd) / 1000;
  
  // Print on Serial Monitor
  Serial.println(String("Scan took " + String(scanTimeSec) + " seconds."));

  // Delete results of last scan
  WiFi.scanDelete();

  // Can We make a function that prints all discovered networks? Yes , see printAllNetworks(int num)
  printAllNetworks(WiFi.scanNetworks());                                                       //uncomment to printall

}


/*   
 * Asynchronous WiFi Networks Scan   
 */ 
 
 void scanAsync() {
  checkCursor(50);
//  Set Color Green to Identify Status message
  tft.setTextColor(ST77XX_GREEN);
  /* Async WiFi works similiar to sync , except its not blocking ,
     you can get number of networks found by WiFi.scanComplete() call
     Call Async by setting parameter async = true
  */
  Serial.println("\n\nAsync (Non-Blocking) Network Scan!");
  tft.println("\n\nAsync (Non-Blocking) Network Scan!");
  //  Note start time
  unsigned long beginScan = millis();
  WiFi.scanNetworks(true);
  
  // You can do other stuff while this scan happens in background
  pinMode(LED_BUILTIN, OUTPUT);
  // While WiFi scan is not completed , toggle LED.
  // scanComplete returns a value < 0 if not complete(-1) or not triggered scan(-2)
  // NOTE : CONCURRENTLY
  int scanFound = WiFi.scanComplete();
  while (scanFound < 0) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(100);
    Serial.println("Doing this while scanning happens in background!!");
    scanFound = WiFi.scanComplete();
  }
  //  Calculate time elapsed in scan
  unsigned long endScan = millis() - beginScan;
  float secScan = float(endScan) / 1000;
  Serial.println("\nScan took" + String(secScan) + " seconds.");
  tft.println("\nScan took" + String(secScan) + " seconds.");
  printAllNetworks(scanFound);
}

void scanAsyncShort() {
  checkCursor(50);
  Serial.println("\n\nBegin Async Short Version Network Scan!");
  //  Note start time
  unsigned long beginScan = millis();
  //  Shorter Set and Forget Version WiFi Async , arguments : <function_on_done(int)>,<isHidden>
  WiFi.scanNetworksAsync(printAllNetworks, false);
  // Do stuff while scan is happening , after done the print function fires automatically(interrupt)
  while (WiFi.scanComplete() < 0) {
    delay(10);
  }
  //  Calculate time elapsed in scan
  unsigned long endScan = millis() - beginScan;
  float secScan = float(endScan) / 1000;
  Serial.println("Scan took" + String(secScan) + " seconds.");
}
