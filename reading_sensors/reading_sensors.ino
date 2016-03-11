// Libraries
#include "Arduino.h"
#include <ArduinoJson.h>
#include "FS.h"
//#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000(); // Create a class for the HDC Sensor
ESP8266WebServer server ( 80 ); // Create an ESP8266 Server class
ESP8266WiFiMulti wifiMulti; // Create an ESP8266 Multi WiFi class
WiFiClient client; // Create an ESP8266 WiFiClient class.
WiFiClientSecure sslclient;

// Variable Definitions
const int hdc_sda = 14; // SDA port for the HDC1000
const int hdc_scl = 2; // SCL port for the HDC1000
const int ledWiFi = 16; // LEDs are going to be used.
const char *dnsName = "esp8266-01"; // DNS Name

// Set WiFi constants
//const char* ssid1     = "SSID_1";
//const char* password1 = "PASS_1";
//const char* ssid2     = "SSID_2";
//const char* password2 = "PASS_2";
//const char* ssid3     = "SSID_3";
//const char* password3 = "PASS_3";

// Functions
void setupDNS(void);
void connectWiFi(void);
char getWiFiAddress(void);
//void sendWiFiAddress(void);
void handleRoot();
void handleSensors();
void handleNotFound();
void handleTemperature();
void handleTemperatureC();
void handleTemperatureF();
void handleTemperatureK();
void handleHumidity();
float getTempCelsius(void);
float getTempFahrenheit(void);
float getTempKelvin(void);
float getHumidityRH(void);
bool loadIndex(void);

// Sketch Code
void setup ( void ) {
  pinMode ( ledWiFi, OUTPUT );
  //  digitalWrite ( ledWiFi, 1 );
  Serial.begin ( 115200 );

  // Connect to Wifi
  connectWiFi();

  // Setup mDNS
  setupDNS();

  // Send the WiFi address out.
  // NOTE: This isn't sending the IP, just a <blank>
  // sendWiFiAddress();

  Serial.println("\nSetting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("\nCouldn't find sensor!");
    while (1);
  }

  server.on ( "/", handleRoot );
  server.on ( "/file", loadIndex );
  server.on ( "/sensors", handleSensors );
  server.on ( "/temperature", handleTemperature );
  server.on ( "/temperature/celsius", handleTemperatureC );
  server.on ( "/temperature/fahrenheit", handleTemperatureF );
  server.on ( "/temperature/kelvin", handleTemperatureK );
  server.on ( "/humidity", handleHumidity );
  server.on ( "/test", []() {
    server.send ( 200, "text/plain", "<p>this works as well</p>" );
  } );
  server.onNotFound ( handleNotFound );
  server.begin();
  Serial.println ( "\nHTTP server started" );

  //  digitalWrite ( ledWiFi, 0 );
}

void loop ( void ) {
  //  digitalWrite ( ledWiFi, 0 );
  server.handleClient();

  //
  //  getWiFiAddress();
  //
  //  Serial.print("Temp: ");
  //  Serial.print(getTempCelsius());
  //  Serial.print("C / ");
  //  Serial.print(getTempFahrenheit());
  //  Serial.print("F");
  //  Serial.print("\tHum: ");
  //  Serial.println(getHumidityRH());
  //
  ////  digitalWrite ( ledWiFi, 1 );
  ////  delay(180000); // 3 minutes
  ////  delay(30000); // 30 seconds
  //  delay(500); // .5 seconds
}

