// Display "Hello World on the screen"
//
// Picture

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735


#include <DHT.h>          // DHt librrary

#define TFT_CS         16
#define TFT_RST        0
#define TFT_DC         4

#define DHTPIN        5         //Defines to  tell which pin is dht 
#define DHTTYPE       DHT22

// Instantiate an object of ST7735
// Making a copy of the Adafruit_ST7735 Blueprint and naming it tft
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Make a DHT class object call it dht
DHT dht = DHT(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  
  dht.begin();              //DHT initialize
  
  Serial.println("Screen initializing");
  // The command is tft.begin() kind of
  tft.initR(INITR_144GREENTAB);
  Serial.println("Screen Initialized");

  // Clear my screen
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextWrap(true);

  // (xpos,ypos,w,h,color)
  tft.fillRoundRect(20, 20 , 90 , 40,5 , ST77XX_WHITE);

  tft.setCursor(25, 25);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_RED,ST77XX_WHITE);
  tft.println("Hello, World!");

  delay(3000);
  tft.setCursor(25, 25);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_RED,ST77XX_WHITE);
  tft.println("Hello, Milind!");
  

}
unsigned long beginTime = 0; 

void loop() {
  // put your main code here, to run repeatedly:
 
 unsigned long timeElapsed = millis();  // Gives time in ms , since MCU start
 float timeElapsedFloat = float(timeElapsed) / 1000; 
  tft.setCursor(15, 35);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_RED,ST77XX_WHITE);
  tft.print("Time Elapsed: ");
  tft.println(timeElapsedFloat);

// Check if 2 seconds have passed
if(millis() - beginTime > 2000){
  
  tft.setCursor(10, 65);  
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.print("Temp (cel): ");
  tft.println(String(dht.readTemperature()));

  tft.setCursor(10, 75);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  tft.print("Humidity: ");
  tft.println(String(dht.readHumidity()));

  beginTime = millis();
}
}
