// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md

// Libraries
#include "Arduino.h"

// Mount the file system

bool loadIndex() {
  File indexFile = SPIFFS.open("/data/index.html", "r");
  if (!indexFile) {
    Serial.println("Failed to open index file");
    return false;
  } else {
    Serial.println(indexFile);
  }
}
