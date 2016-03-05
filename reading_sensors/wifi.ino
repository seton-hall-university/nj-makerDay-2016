// Libraries
#include "Arduino.h"

void connectWiFi() {
  wifiMulti.addAP(ssid1, password1);        //if you have less SSID, delete the others
  wifiMulti.addAP(ssid2, password2);
//  wifiMulti.addAP(ssid3, password3);

  Serial.println("Connecting WiFi...");
  
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
  Serial.println("Connecting...");
  }

  digitalWrite ( ledWiFi, 1 );
  Serial.println( "WiFi Connected" );
  getWiFiAddress();
}

char getWiFiAddress(void) {
  // Print the IP address out to the serial connection
//  Serial.print ( "\n\nIP address: " );
//  Serial.println ( WiFi.localIP() );

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  return WiFi.localIP();
}
