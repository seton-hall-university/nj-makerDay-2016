// Libraries
#include "Arduino.h"

float getHumidityRH(void) {
  return hdc.readHumidity();
}

void handleHumidity() {
  String json = "";
  json += "{\"humidity\":{\"relative\":";
  json += getHumidityRH();
  json += "}}";
  server.send ( 200, "application/json", json );
}
