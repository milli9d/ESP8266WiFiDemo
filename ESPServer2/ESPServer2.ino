#include "ESP_MS.h"
#include "server_io.h"
#include "tft_ms.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  tft_setup();
  pinMode(LED, OUTPUT);       //Built-In LED Pin
  pinMode(LED2, OUTPUT);       //Built-In LED Pin
  dht.begin();
  // Function Calls
   SSID_Scan();                // to see all avaialble networks(Uncomment)
  WiFiConnect();              // Connect to defined SSID and PASS
  // Server
  mainServer();
  WiFi.printDiag(Serial);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
