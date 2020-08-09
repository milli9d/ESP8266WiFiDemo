// Preprocessor includes
#include "ILI9341_SPI.h"
#include <MiniGrafx.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>
#include "weather_logo.h"
#include "weathericons.h"
#include "fonts.h"

//PINOUT for lcd screen and touchscreen
#define STMPE_CS 16
#define TFT_CS 0
#define TFT_DC 15
#define SD_CS 2
#define TFT_LED 5

//Preprocessor defines
#define WIFI_SSID "Boom Nation 2G"
#define WIFI_PASS "boomboomboom"
#define MAX_FORECAST 3

//Palette colors
#define BLACK_COLOR 0x0000
#define WHITE_COLOR 0xFFFF
#define BLUE_COLOR 0x7E3C


//Define time constraints
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600; // -4 UTC Offset/ New York
NTPClientUpdated timeClient(ntpUDP, "pool.ntp.org" , utcOffsetInSeconds);

//Intitializations
String timeStamp;
String dateStamp;
int screen = 1;
boolean isDebug = false;

// weather settings
String OPEN_WEATHER_MAP_LANGUAGE = "en";
String OPEN_WEATHER_MAP_APPID = "d4b26391d35fe98cace3b9f4e49c6ff9";
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US";
const boolean IS_METRIC = true;

// Weather objects
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECAST];

// Graphics lib initialization
int BITS_PER_PIXEL = 2; //2 ^ 2 = 4 colors
uint16_t palette[] = {
  BLACK_COLOR, //0
  WHITE_COLOR, //1
  ILI9341_YELLOW, //2
  BLUE_COLOR, //3
};

ILI9341_SPI tft = ILI9341_SPI (TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx (&tft, BITS_PER_PIXEL, palette);

void welcomeScreen() {
  gfx.fillBuffer(0);
  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 30, "WEATHER STATION");
  gfx.drawPalettedBitmapFromPgm(60, 60, weather_icon);
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 290, "Monish Kapadia");
  gfx.commit();
}

void drawProgress(int percentage, String text) {
  gfx.fillBuffer(0);
  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 30, "WEATHER STATION");
  gfx.drawPalettedBitmapFromPgm(60, 60, weather_icon);

  // ProgressBasr
  gfx.setColor(3);
  gfx.drawRect(10, 198, 220, 15);
  gfx.setColor(3);
  gfx.fillRect(12, 200, 216 * percentage / 100 , 11);

  // Text for more info
  gfx.setColor(1);
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 230, text);

  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 290, "Monish Kapadia");
  gfx.commit();
}

void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  Serial.print(WIFI_SSID);
  Serial.print("/");
  Serial.println(WIFI_PASS);
  Serial.print("Connecting to the WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (i > 90) {
      i = 0;
    }
    i = i + 10;
    drawProgress(i, "Connecting to Wifi (" + String(WIFI_SSID) + ")");
    Serial.print(".");
  }
  drawProgress(100, "Connected to Wifi (" + String(WIFI_SSID) + ")");
  Serial.println("\nConnected to the WiFi");
}

void updateWeatherData() {
  // Current Weather
  drawProgress(50, "Updating Current Weather...");
  OpenWeatherMapCurrent *currentWeatherClient = new OpenWeatherMapCurrent();
  currentWeatherClient->setMetric(IS_METRIC);
  currentWeatherClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient->updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION);
  delete currentWeatherClient;
  currentWeatherClient = nullptr;

  delay(100);
  //Forecast Weather
  drawProgress(80, "Updating Forecasts Weather...");
  OpenWeatherMapForecast *forecastClient = new OpenWeatherMapForecast();
  forecastClient->setMetric(IS_METRIC);
  forecastClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  forecastClient->updateForecasts(forecasts, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECAST);
  delete forecastClient;
  forecastClient = nullptr;

  delay(100);
}

void weatherScreen() {
  gfx.fillBuffer(0);
  // Time at y=20
  gfx.setFont(Lato_Regular_28);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 15, timeStamp);

  // Date at y=55
  gfx.setFont(Lato_Bold_20);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 50, dateStamp);

  //Display temperature
  gfx.setFont(Lato_Black_45);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
  gfx.setColor(1);
  gfx.drawString(220, 105, String(int(round(currentWeather.temp))) + "°C");

  //Display temperature
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
  gfx.setColor(1);
  gfx.drawString(220, 155, String(currentWeather.description));

  // Display the weather icon
  gfx.drawPalettedBitmapFromPgm(10, 85, getMeteoconIconFromProgmem(currentWeather.icon));

  // In 3 hrs
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(40, 200, "3 hrs");

  gfx.drawPalettedBitmapFromPgm(15, 220, getMiniMeteoconIconFromProgmem(forecasts[0].icon));

  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(40, 280, String(int(round(forecasts[0].temp))) + "°C");

  // In 6 hrs
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 200, "6 hrs");

  gfx.drawPalettedBitmapFromPgm(95, 220, getMiniMeteoconIconFromProgmem(forecasts[1].icon));

  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 280, String(int(round(forecasts[1].temp))) + "°C");

  // In 9 hrs
  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(200, 200, "9 hrs");

  gfx.drawPalettedBitmapFromPgm(175, 220, getMiniMeteoconIconFromProgmem(forecasts[2].icon));

  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(200, 280, String(int(round(forecasts[2].temp))) + "°C");

  gfx.setFont(Lato_Regular_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 300, String(currentWeather.cityName));
  
  gfx.commit();
}

void todaysInformation() {
  gfx.fillBuffer(0);

  gfx.setTextAlignment(TEXT_ALIGN_LEFT);
  
  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 10, "Temperature(Min): " + String(int(round(currentWeather.tempMin))) + "°C");
  
  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 40, "Temperature(Max): " + String(int(round(currentWeather.tempMax))) + "°C");

  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 70, "Humidity: " + String(currentWeather.humidity) + "%");

  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 100, "Pressure: " + String(currentWeather.pressure) + " mb");

  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 130, "Sunrise: " + String(timeClient.getFormattedTime(true, currentWeather.sunrise + utcOffsetInSeconds)));

  gfx.setFont(Lato_Bold_20);
  gfx.setColor(1);
  gfx.drawString( 10, 160, "Sunset: " + String(timeClient.getFormattedTime(true, currentWeather.sunset + utcOffsetInSeconds)));

  
  gfx.commit();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  Serial.begin(115200);
  Serial.print("\n\n\n");
  gfx.init();
  welcomeScreen();
  delay(1000);
  connectWiFi();
  updateWeatherData();
  timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (!timeClient.forceUpdate()) {
    timeClient.forceUpdate();
  }


  if (millis() % 3600000 < 1500) {
    updateWeatherData();
  }

  if (millis() % 10000 < 150) {
    if (screen == 1) {
      screen = 2;
    } else if (screen == 2) {
      screen = 1;
    }
  }

  timeStamp = timeClient.getFormattedTime();
  dateStamp = timeClient.getFormattedDate();

  if (screen == 1) {
    weatherScreen();  
  } else if (screen == 2) {
    todaysInformation();
  }
  

  if (isDebug) {
    Serial.println("Time: " + timeStamp);
    Serial.println("Date: " + dateStamp);
    Serial.println("Temp: " + String(int(round(currentWeather.temp))) + "°C");
    Serial.println("3 hour forecast");
    Serial.println("Temp: " + String(int(round(forecasts[0].temp))) + "°C");
    Serial.println("6 hour forecast");
    Serial.println("Temp: " + String(int(round(forecasts[1].temp))) + "°C");
    Serial.println("9 hour forecast");
    Serial.println("Temp: " + String(int(round(forecasts[2].temp))) + "°C");
    Serial.println("---------------------------------------------");
    delay(1000);
  }
  delay(10);
  
}
