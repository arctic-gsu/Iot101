#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

#define WIFI_AP "Aluth"
#define WIFI_PASSWORD "Sumanadasa1947"

#define TOKEN "PprXRfOajb2fE1g03iXO"
char thingsboardServer[] = "192.168.0.204";
WiFiClient wifiClient;
ThingsBoard tb(wifiClient);
long data1;
long data2;
int status = WL_IDLE_STATUS;
unsigned long lastSend;
void setup()
{
  Serial.begin(115200);
  InitWiFi();
  lastSend = 0;
}

void loop()
{
  if ( !tb.connected() ) {
    reconnect();
  }
  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    SendData();
    lastSend = millis();
  }
  tb.loop();
}
void SendData()
{
data1 = random(10, 20);
data2 =  random(30, 70);
  tb.sendTelemetryFloat("data1", data1);
  tb.sendTelemetryFloat("data2", data2);
}
void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}
void reconnect() {
  // Loop until we're reconnected
  while (!tb.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
