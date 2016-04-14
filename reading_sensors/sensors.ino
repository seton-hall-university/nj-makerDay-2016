// Libraries
#include "Arduino.h"


void handleSensors() {
  String json = "";
  json += "{\"sensors\":";
  json += "{\"humidity\":{\"relative\":";
  json += getHumidityRH();
  json += "},";
  json += "{\"temperature\":{\"celsius\":";
  json += getTempCelsius();
  json += ",\"fahrenheit\":";
  json += getTempFahrenheit();
  json += ",\"kelvin\":";
  json += getTempKelvin();
  json += "}}";
  json += "}";
  server.send ( 200, "application/json", json );
  json = String();
}
