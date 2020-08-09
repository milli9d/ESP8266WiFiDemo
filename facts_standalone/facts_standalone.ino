#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ArduinoJson.h>
#include "ESP_MS.h"

#define hline Serial.println("======================================================================================")

const char* facturl =  "http://numbersapi.com/random";
const char* timeurl =  "http://evilinsult.com/generate_insult.php?lang=en&type=text";
const char* quoteurl =  "http://api.forismatic.com/api/1.0/?method=getQuote&format=text&lang=en";
//const char* timeurl =  "http://worldtimeapi.org/api/ip.txt";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();

  WiFiConnect();


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("+++++++++ FACT OF THE TIME!!! +++++++++");
  hline;
  HTTPClient factClient;
  factClient.begin(facturl);
  if (factClient.GET() > 0) {
    String fact = factClient.getString();
    Serial.println(fact);
  }
  factClient.end();
  Serial.println();
  Serial.println("+++++++++++++ FOOD FOR THOUGHT +++++++++++++");
  hline;
  HTTPClient quoteClient;
  quoteClient.begin(quoteurl);
  if (quoteClient.GET() > 0) {
    String timestr = quoteClient.getString();
    Serial.println(timestr);
  }
  quoteClient.end();
  Serial.println();
  Serial.println("+++++++++++++    AN INSULT     +++++++++++++");
  hline;
  HTTPClient timeClient;
  timeClient.begin(timeurl);
  if (timeClient.GET() > 0) {
    String timestr = timeClient.getString();
    Serial.println(timestr);
  }
  timeClient.end();
  Serial.println();
  delay(5 * 1000);
}
