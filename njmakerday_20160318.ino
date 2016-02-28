// Libraries
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Adafruit_HDC1000.h"
#include <Wire.h>

Adafruit_HDC1000 hdc = Adafruit_HDC1000(); // Create a class for the HDC Sensor
ESP8266WebServer server ( 80 ); // Create an ESP8266 Server class
WiFiClient client; // Create an ESP8266 WiFiClient class.

// Program Variables
bool debug = 0; // Debug mode allows printing to the serial port.
const int hdc_sda = 14; // SDA port for the HDC1000
const int hdc_scl = 2; // SCL port for the HDC1000
const int ledWiFi = 16; // LEDs are going to be used.
const char *dnsName = "esp8266-lee"; // DNS Name
//float currentTemp = 0.000; // variable to store current temp
//float currentHumidity = 0.000; // variable to store current humidity

// Set WiFi constants
//const char *ssid = "@400SoAve#";
//const char *password = "589ShU!$305";
const char *ssid = "theNile";
const char *password = "stereo!3";

// Functions
void connectWiFi();
char getWiFiAddress(void);
void handleRoot();
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

// Sketch Code
void setup ( void ) {
	pinMode ( ledWiFi, OUTPUT );
//  digitalWrite ( ledWiFi, 1 );
  Serial.begin ( 115200 );
  
  // Connect to Wifi
  connectWiFi();
  
  Serial.println("Setting up HDC100x...");
  Wire.begin(hdc_sda, hdc_scl);
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
  }
  
	server.on ( "/", handleRoot );
  server.on ( "/temperature", handleTemperature );
  server.on ( "/temperature/celsius", handleTemperatureC );
  server.on ( "/temperature/fahrenheit", handleTemperatureF );
  server.on ( "/temperature/kelvin", handleTemperatureK );
  server.on ( "/humidity", handleHumidity );
	server.on ( "/inline", []() {
		server.send ( 200, "text/plain", "this works as well" );
	} );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );
 
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

