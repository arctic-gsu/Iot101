#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define WIFI_AP ""
#define WIFI_PASSWORD ""
#define TOKEN ""
char thingsboardServer[] = "";
WiFiClient wifiClient;
PubSubClient client(wifiClient);
int status = WL_IDLE_STATUS;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 client.setServer( thingsboardServer, 1883 );
 client.setCallback(on_message);
 if ( client.connect("ESP8266 Device", TOKEN, NULL) ) {
      Serial.println( client.connected() );
      // Subscribing to receive RPC requests
      client.subscribe("v1/devices/me/rpc/request/+");
      Serial.println(client.state());
      // Sending current GPIO status
//      Serial.println("Sending current GPIO status ...");
//      client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
    } 

    
}


void loop() {
if ( !client.connected() ) {
reconnect();
}

client.loop();
}

void on_message(const char* topic, byte* payload, unsigned int length) {

Serial.println("On message");

char json[length + 1];
strncpy (json, (char*)payload, length);
json[length] = '\0';

Serial.print("Topic: ");
Serial.println(topic);
Serial.print("Message: ");
Serial.println(json);
}

void reconnect() {
// Loop until we're reconnected
while (!client.connected()) {
status = WiFi.status();
if ( status != WL_CONNECTED) {
WiFi.begin(WIFI_AP, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("Connected to AP");
}
Serial.print("Connecting to Thingsboard node ...");
// Attempt to connect (clientId, username, password)
if ( client.connect("ESP8266 Device", TOKEN, NULL) ) {
Serial.println( "[DONE]" );
// Subscribing to receive RPC requests
client.subscribe("v1/devices/me/rpc/request/+");
// Sending current GPIO status
Serial.println("Sending current GPIO status ...");
//client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
} else {
Serial.print( "[FAILED] [ rc = " );
Serial.print( client.state() );
Serial.println( " : retrying in 5 seconds]" );
// Wait 5 seconds before retrying
delay( 5000 );
}
}
}
