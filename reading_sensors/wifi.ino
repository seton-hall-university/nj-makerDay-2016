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
  Serial.println( "\nWiFi Connected" );
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
  Serial.println(" dBm\n");

  return WiFi.localIP();
}

void sendWiFiAddress(void) {
  IPAddress ip = WiFi.localIP();
  byte oct1 = ip[0];
  byte oct2 = ip[1];
  byte oct3 = ip[2];
  byte oct4 = ip[3];
  char s[16];
  sprintf(s, "%d.%d.%d.%d", oct1, oct2, oct3, oct4);
  Serial.print("IP \"char\" = ");
  Serial.println(s);
  
  const char* serverHost = "maker.ifttt.com";
  const int serverPort = 443;
  String serverPath = "/trigger/esp8266-01-connected/with/key/bIZaJeZz4iLcCUnI9wkCQ6";
  String serverPayload = String("POST ") + serverPath + " HTTP/1.1\r\n" +
  "Host: " + serverHost + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" +
  "Connection: close\r\n\r\n" + "{\"value1\":\"" + s + "\"}";

  Serial.println("\nSending IP Address...");
  
  
//  Serial.print("Client Connected? ");
//  Serial.println(client.connect(serverHost, serverPort));
  
  if (sslclient.connect(serverHost, serverPort)) {
    Serial.print("Client Connected? ");
    Serial.println(sslclient.connected());
    
    Serial.print("connecting to ");
    Serial.println(serverHost);
    Serial.print("requesting URL: ");
    Serial.println(serverPath);
    Serial.print("posting: ");
    Serial.println(serverPayload);
    
    sslclient.print(serverPayload);
    
    Serial.println("request sent");
    while (sslclient.connected()) {
      String line = sslclient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }
    
    String line = sslclient.readStringUntil('\n');
    
    Serial.println("Reply was:");
    Serial.println("==========");
    Serial.println(line);
    Serial.println("==========");
    Serial.println("Closing connection");
    
  } else {
    // You didn't get a connection to the server:
    Serial.println("\nConnection failed");
  }
}

