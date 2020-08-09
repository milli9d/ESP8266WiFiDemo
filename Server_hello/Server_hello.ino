#include "ESP_MS.h"

int LED = 15;
int LED2 = 5;
static float temp = 0;

static ESP8266WebServer server(7777);
static DHT dht(DHTPIN, DHTTYPE);

#define hline Serial.println("======================================================================================")

const char* facturl =  "http://numbersapi.com/random";
const char* timeurl =  "http://evilinsult.com/generate_insult.php?lang=en&type=text";
const char* quoteurl =  "http://api.forismatic.com/api/1.0/?method=getQuote&format=text&lang=en";
//const char* timeurl =  "http://worldtimeapi.org/api/ip.txt";

WiFiClient client;

void rootHandle() {
  Serial.println("Root Handle");
  server.send(200, "text/html", menupage);
}

void LEDHandle() {
  digitalWrite(LED, !digitalRead(LED));
  server.send(200, "text/html", menupage);
}

void LED2Handle() {
  digitalWrite(LED2, !digitalRead(LED2));
  server.send(200, "text/html", menupage);
}

String genDHT() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  return ("Temperature: "+ String(temp) + " Celcius\t Humidity :"+ String(hum)+"%");
}

void DHTHandle() {  
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
    server.send(200, "text/plain",head+"\n"+ quotestr);
    Serial.println(quotestr);
  }
  quoteClient.end();
  Serial.println();
}

void mainServer() {
  server.on("/", rootHandle);
  server.on("/LED", LEDHandle);
  server.on("/LED2", LED2Handle);
  server.on("/DHT", DHTHandle);
  server.on("/Q", QHandle);
  server.begin();
  Serial.print("Server started on ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  pinMode(LED, OUTPUT);       //Built-In LED Pin
  pinMode(LED2, OUTPUT);       //Built-In LED Pin
  dht.begin();

  // Function Calls
  // SSID_Scan();                // to see all avaialble networks(Uncomment)
  WiFiConnect();              // Connect to defined SSID and PASS

  // Server
  mainServer();
  WiFi.printDiag(Serial);

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  Serial.println("Running");
}
