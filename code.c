#include <Arduino.h>
#include "WiFi.h"
#include <PubSubClient.h>

#define WIFI "Wokwi-GUEST"
#define PASSWORD ""
#define TIMEOUT 2000
#define BROKER "broker.hivemq.com"
#define TOPIC "okforreal"
#define OUTTOPIC "ok"


WiFiClient esp;
PubSubClient client(esp);

int count = 0;
char* message = "risat the goat";

void connectwifi(){
  Serial.println("connecting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI, PASSWORD);

  unsigned long start = millis();
  while(WiFi.status() != WL_CONNECTED && millis()-start < TIMEOUT){
    Serial.println("in");
    delay(100);
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("failed");
  }
  else{
    Serial.println("connected");
    Serial.println(WiFi.localIP());
  }
}


void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("recieved:");
  for(int i = 0; i<length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println();
}

void reconnect(){
  while(!client.connected()){
    Serial.println("Connected to: ");
    Serial.println(BROKER);
    if(client.connect("esptesterfr")){
      Serial.println("connected");
      client.subscribe(OUTTOPIC);
    }
  }
}
void setup() {
  Serial.begin(115200);
  connectwifi();
  client.setServer(BROKER, 1883);
  client.setCallback(callback);
  Serial.println("Hello, ESP32!");
}
unsigned long starttime = millis();
//millis()-starttime<2000

void loop() {
  if(!client.connected()){
    reconnect();
    starttime = millis();
  }
  /*if(millis()-starttime<2000){
    count++;
    //snprintf(message, 10, "%ld", count);
    Serial.println();
    client.publish(TOPIC, message);
  }*/
}
