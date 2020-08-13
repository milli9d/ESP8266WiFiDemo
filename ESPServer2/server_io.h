#pragma once
#include "ESP_MS.h"

void rootHandle() {
  clrScr();
  tft.setTextSize(3);
  drawText("Client\n" , ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("Connected");
  tft.setTextSize(1);
  Serial.println("Root Handle");
  server.send(200, "text/html", menupage);
}

void mainServer() {
  server.on("/", rootHandle);
  server.on("/LED", LEDHandle);
  server.on("/LED2", LED2Handle);
  server.on("/DHT", DHTHandle);
  server.on("/Q", QHandle);
  server.on("/clr", clrHandle);
  server.begin();
  serverStatus();

}

void LEDHandle() {
  Serial.println("LED Handle");
  bool flag = !digitalRead(LED);
  tft.setTextColor(ST77XX_GREEN);
  tft.printf("\nLED STATUS : %s", flag ? "On" : "Off");
  tft.setTextColor(ST77XX_WHITE);
  digitalWrite(LED, flag);
  server.send(200, "text/html", menupage);
}


void clrHandle() {
  clrScr();
  server.send(200, "text/html", menupage);
}

void serverStatus() {
  tft.println();
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(3);
  drawTextln("Server\nStarted", ST77XX_RED);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("\n");
  Serial.print("\t\t\tServer Started \n");
  Serial.print(WiFi.localIP());
  tft.print("\n\nVisit(HTTP):\n\n");
  tft.println(R"(108.46.156.22:7777/)");
  tft.println("\n\n");
  tft.print("=========");
  tft.setTextColor(ST77XX_RED);
  tft.println(F("Milind Singh"));
  tft.setTextColor(ST77XX_WHITE);
}


void LED2Handle() {
  Serial.println("LED2 Handle");
  bool flag = !digitalRead(LED2);
  tft.setTextColor(ST77XX_BLUE);
  tft.printf("\nLED2 STATUS : %s", flag ? "Off" : "On");
  tft.setTextColor(ST77XX_WHITE);
  digitalWrite(LED2, flag);
  server.send(200,"text/html",menupage );
}

String genDHT() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String gen = String("Temperature: " + String(temp) + " Celcius\t Humidity :" + String(hum) + "%");
  Serial.println(gen);
  tft.println();
  tft.print(String("T: " + String(temp) + "c H: " + String(hum)+"%"));
  return gen;
}

void DHTHandle() {
  Serial.println("DHT Handle");
  //  server.send(200, "text/html", dhtPage);
  server.send(200, "text/plain", genDHT());
}

void QHandle() {
  String head = "+++++++++++++ FOOD FOR THOUGHT +++++++++++++";
  Serial.println(head);
  hline;
  HTTPClient quoteClient;
  quoteClient.begin(quoteurl);
  if (quoteClient.GET() > 0) {
    String quotestr = quoteClient.getString();
    server.send(200, "text/plain", head + "\n" + quotestr);
    Serial.println(quotestr);
  }
  quoteClient.end();
  Serial.println();
}
