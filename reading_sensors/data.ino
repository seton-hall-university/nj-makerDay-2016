// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md

// Libraries
#include "Arduino.h"

// Mount the file system
bool gotMounted = SPIFFS.begin();

bool checkMount() {
  if (gotMounted) {
    Serial.println("We've got files!");
    return true;
  } else {
    Serial.println("We don't got files!");
    return false;
  }
}

bool loadIndex() {
  checkMount;
  File indexFile = SPIFFS.open("index.html", "r");
  if (!indexFile) {
    Serial.println("Failed to open index file");
    return false;
  } else {
    Serial.println(indexFile);
  }
}
