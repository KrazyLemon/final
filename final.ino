#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>
#include "DHT.h"

// ------------------- Wifi ------------------------- //
const char* ssid = "Megacable-2FC0";
const char* password = "nhJn3XY4VL";
// ------------------- Sensores  ------------------------- //
#define soil_moisture_pin 32
DHT dht(4, DHT11);

float temp; // Temperatura del DHT
float hum;  // Humedad del aire DHT
float heat; // Indice de Calor
float moist; // Humedad del Suelo

// ------------------- API's ------------------------- //
String api = "https://pied-test.000webhostapp.com/Esp32_post.php";
const char* servername = "pied-test.000webhostapp.com/esp-outputs-action.php?action=outputs_state&board=1";

// ------------------- Variables ------------------------- //
const long interval = 3000;
unsigned long previousMillis = 0;

String outputsState;

// ------------------- Conexion a Wifi ------------------------- //
void initWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.println("Intentando Conectar a red Wifi");
  int timed_out = 20;
  timed_out = timed_out *2;

  while(WiFi.status()!= WL_CONNECTED){
    Serial.print(".");
    delay(3000);
    if(timed_out > 0) {
      timed_out = timed_out -1;
    }
    if(timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }
  Serial.println("Connectado a Wifi Correctamente");
  // Serial.println(WiFi.localIP());
  delay(5000);
}
// ------------------- Funcion para obtener las lecturas de los sensores ------------------------- //
void getDHTReads(){
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp) ) {
    Serial.println(F("Fallo de conexion con el DHT"));
    hum = 0.00;
    temp= 0.00;
    return;
  }
  heat = dht.computeHeatIndex(temp, hum, false);
  moist = analogRead(soil_moisture_pin);

}
// ------------------- Funcion POST Bomba  ------------------------- //
void bombaloop(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
      outputsState = httpGETRequest(serverName);
      Serial.println(outputsState);
      JSONVar myObject = JSON.parse(outputsState);

      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      JSONVar keys = myObject.keys();
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        // Serial.print("GPIO: ");
        // Serial.print(keys[i]);
        // Serial.print(" - SET to: ");
        // Serial.println(value);
        pinMode(atoi(keys[i]), OUTPUT);
        digitalWrite(atoi(keys[i]), atoi(value));
      }
      previousMillis = currentMillis;
    }
  }
}
// ------------------- Funcion GET Bomba ------------------------- //
String httpGETRequest(const char* serverName) {
  WiFiClientSecure *client = new WiFiClientSecure;
  
  // set secure client without certificate
  client->setInsecure();
  HTTPClient https;
    
  // Your IP address with path or Domain name with URL path 
  https.begin(*client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = https.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = https.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  https.end();

  return payload;
}
// ------------------- Funcion post DHT11 ------------------------- //
void EnvioDatos(){
  HTTPClient http;
  String datos_a_enviar = "dht_humidity=" + String(hum) + "&dht_temperature=" + String(temp) + "&dht_heat=" + String(heat) + "&soil_moisture=" + String(moist);
  http.begin(api); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int codigo_respuesta = http.POST(datos_a_enviar); 
  if(codigo_respuesta>0){
    Serial.println("Código HTTP ► " + String(codigo_respuesta)); 
    if(codigo_respuesta == 200){
      String cuerpo_respuesta = http.getString();
      Serial.println("El servidor respondió ▼ ");        
      Serial.println(cuerpo_respuesta);
    }
  }else{
    Serial.print("Error enviando POST, código: ");
    Serial.println(codigo_respuesta);
  }
  http.end();  //libero recursos
}
// ------------------- Setup Function ------------------------- //
void setup() {
  Serial.begin(115200);
  pinMode(output27, OUTPUT);
  digitalWrite(output27, HIGH);
  initWifi();
  dht.begin();
}
// ------------------- Loop Function ------------------------- //
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    bombaloop();
    getDHTReads();
    EnvioDatos();
    delay(60000);
  }else {
     Serial.println("Error en la conexion WIFI");
  }
}
