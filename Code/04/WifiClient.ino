
/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "ESP8266Ping.h"
#ifndef STASSID
#define STASSID "ssid"
#define STAPSK "password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
const char* remote_host = "google.com";


ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);
}


void loop() {
if(Ping.ping(remote_host)) {
    Serial.println("Online");
    delay(1000);
    
    
  } else {
    
    Serial.println("Offline");
    delay(1000);
    
    
  }
}
