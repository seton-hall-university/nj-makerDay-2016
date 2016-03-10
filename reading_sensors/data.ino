// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md

// Libraries
#include "Arduino.h"

// Mount the file system
//bool SPIFFS.begin();

Dir dir = SPIFFS.openDir("/data");

while (dir.next()) {
    Serial.print(dir.fileName());
    File f = dir.openFile("r");
    Serial.println(f.size());
    f.close();
}

bool loadIndex() {
  File indexFile = SPIFFS.open("/data/index.html", "r");
  if (!indexFile) {
    Serial.println("Failed to open index file");
    return false;
  } else {
    Serial.println(indexFile);
  }

