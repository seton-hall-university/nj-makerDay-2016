// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md

// Libraries
#include "Arduino.h"

// Mount the file system
bool checkMount() {
  delay(1000);
  Serial.println("Mounting FS...");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return false;
//  } else {
//    Serial.println("We got files!");
//    return;
  }
}

// Load the index HTML file
bool loadIndex() {
  // checkMount();
  File indexFile = SPIFFS.open("/data/index.html", "r");
  if (!indexFile) {
    Serial.println("Failed to open index file");
    return false;
  } else {
    Serial.print(indexFile);
    return indexFile;
  }
}
