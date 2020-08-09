// ESP8266 WiFi Demos - Milind Singh | Aug 2020
// 01 - ESP8266 WiFi Scan Class Demo

#include <ESP8266WiFi.h>                               // Include ESP WiFi Library

// Supplementary function to print all networks
void printAllNetworks(int num) {
  //  If no networks are discovered
  if (num <= 0) {
    Serial.println("No Networks Found!");
  }
  //  If networks found , run for loop on number of networks and fetch/print information
  else {
    Serial.println(String(num) + " networks found!");
    for (int i = 0 ; i < num ; i++) {
      Serial.println(String(String(i) + ".SSID = " + String(WiFi.SSID(i)) + " RSSI" + String(WiFi.RSSI(i))));
    }
  }
}

//  01 Synchronous WiFi Networks Scan ==================================================================================================
void scanSync() {
  Serial.println("\n\nBegin Sync(Blocking) Network Scan!");
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

  /* To access WiFi Info use WiFi
    WiFi.RSSI(networkItem)  // Return the RSSI (Received Signal Strength Indication) of a network discovered during the scan.
    Other Parameters Similiarly : SSID, encryptionType , BSSID , channel , isHidden
  */
  Serial.println(String("SSID = " + String(WiFi.SSID(0)) + " RSSI" + String(WiFi.RSSI(0))));    //uncomment to print
  Serial.println(String("SSID = " + String(WiFi.SSID(1)) + " RSSI" + String(WiFi.RSSI(1))));

  // Delete results of last scan
  WiFi.scanDelete();

  // Can We make a function that prints all discovered networks? Yes , see printAllNetworks(int num)
  printAllNetworks(WiFi.scanNetworks());                                                       //uncomment to printall

  //=====================================================================================================================================
}


//  02 Asynchronous WiFi Networks Scan ==================================================================================================
void scanAsync() {
  /* Async WiFi works similiar to sync , except its not blocking ,
     you can get number of networks found by WiFi.scanComplete() call
     Call Async by setting parameter async = true
  */
  Serial.println("\n\nBegin Async Network Scan!");
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
  Serial.println("Scan took" + String(secScan) + " seconds.");
  printAllNetworks(scanFound);

  //=====================================================================================================================================
}

void scanAsyncShort(){
  Serial.println("\n\nBegin Async Short Version Network Scan!");
  //  Note start time
  unsigned long beginScan = millis();
  //  Shorter Set and Forget Version WiFi Async , arguments : <function_on_done>,<isHidden>
  WiFi.scanNetworksAsync(printAllNetworks, false);
  // Do stuff while scan is happening , after done the print function fires automatically(interrupt)  
  while(WiFi.scanComplete()<0){
    delay(10);
    }
  //  Calculate time elapsed in scan
  unsigned long endScan = millis() - beginScan;
  float secScan = float(endScan) / 1000;
  Serial.println("Scan took" + String(secScan) + " seconds.");
  }

void setup() {
  //  Begin Serial port 9600 baud
  Serial.begin(9600);
  Serial.println();

  // Go to function body and see detailed explainations
  scanSync();

  scanAsync();
  
  scanAsyncShort();


}

void loop() {
  // Nothing
}
