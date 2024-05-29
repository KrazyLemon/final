#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include "DHT.h"
const char* ssid = "Megacable-2FC0";
const char* password = "nhJn3XY4VL";
DHT dht(4, DHT11);
float temp;
float hum;  
float heat; 
float moist; 
String api = "https://pied-test.000webhostapp.com/Esp32_post.php";
// const char* serverName = "pied-test.000webhostapp.com/esp-outputs-action.php?action=outputs_state&board=1";
// const long interval = 3000;
// unsigned long previousMillis = 0;
// String outputsState;

void setup() {
  Serial.begin(115200);
  initWifi();
  dht.begin();
}
void loop() {
  if(WiFi.status() == WL_CONNECTED){
  //   unsigned long currentMillis = millis();
  // if(currentMillis - previousMillis >= interval) {
  //   outputsState = httpGETRequest(serverName);
  //   JSONVar myObject = JSON.parse(outputsState);
  //   if (JSON.typeof(myObject) == "undefined") {
  //     return;      
  //   }  
  //   JSONVar keys = myObject.keys();
  //   for (int i = 0; i < keys.length(); i++) {
  //     JSONVar value = myObject[keys[i]];
  //     pinMode(atoi(keys[i]), OUTPUT);
  //     digitalWrite(atoi(keys[i]), atoi(value));
  //   }
  //   previousMillis = currentMillis;
  // }
    getDHTReads();
    EnvioDatos();
    delay(60000);
  }
}
void initWifi(){
  WiFi.begin(ssid,password);
  Serial.println("Intentando Conectar a red Wifi");
  int timed_out = 20;
  timed_out = timed_out *2;

  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(500);
    if(timed_out > 0) {
      timed_out = timed_out -1;
    }
    if(timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }
  delay(5000);
}
void getDHTReads(){
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(hum) || isnan(temp) ) {
    hum = 0.00;
    temp= 0.00;
    return;
  }
  heat = dht.computeHeatIndex(temp, hum, false);
  moist = analogRead(32);

}
void bombaloop(){
  
}
// String httpGETRequest(const char* serverName) {
//   WiFiClientSecure *client = new WiFiClientSecure;
//   client->setInsecure();
//   HTTPClient https;
//   https.begin(*client, serverName);
//   int httpResponseCode = https.GET();
//   String payload = "{}"; 
//   if (httpResponseCode>0) {
//     payload = https.getString();
//   }
//   https.end();
//   return payload;
// }
void EnvioDatos(){
  HTTPClient http;
  String datos_a_enviar = "dht_humidity=" + String(hum) + "&dht_temperature=" + String(temp) + "&dht_heat=" + String(heat) + "&soil_moisture=" + String(moist);
  http.begin(api); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int codigo_respuesta = http.POST(datos_a_enviar); 
  if(codigo_respuesta>0){
    if(codigo_respuesta == 200){
      String cuerpo_respuesta = http.getString();
    }
  }
  http.end(); 
}