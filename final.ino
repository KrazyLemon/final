#include <WiFi.h>
#include <HTTPClient.h>
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

String api = "https://pied-test.000webhostapp.com/Esp32_post.php";

WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output27State = "on";

const int output27 = 27;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

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
  Serial.println(WiFi.localIP());
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
// ------------------- Funcion post  ------------------------- //

// ------------------- Funcion post dht ------------------------- //
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
    getDHTReads();
    initserver();
    EnvioDatos();
    delay(60000);
  }else {
     Serial.println("Error en la conexion WIFI");
  }
}
