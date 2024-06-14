#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ------------------- Wifi ------------------------- //
const char* ssid = "Megacable-2FC0";
const char* password = "nhJn3XY4VL";

//const char* ssid = "207_C";
//const char* password = "ISC2024/";
// ------------------- Sensores  ------------------------- //
#define smp_a 26
#define smp_b 25
#define smp_c 33

DHT dht(4, DHT11);
float temp; // Temperatura del DHT
float hum;  // Humedad del aire DHT
float heat; // Indice de Calor
float smp_1; // ------------------------------------------------- //
float smp_2; // -----------Sensores Humedad del Suelo ----------- //
float smp_3; // ------------------------------------------------- //
float moist;

int rojo = 21;
int verde = 18;

// ------------------- API's ------------------------- //
String api = "https://pied-test.000webhostapp.com/dht-api.php";
// ------------------- Conexion a Wifi ------------------------- //
void initWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  Serial.println("Intentando Conectar a red Wifi");
  int timed_out = 30;
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
    digitalWrite(rojo, HIGH);
    delay(3000);
    hum = 0.00;
    temp= 0.00;
    return;
  }
  heat = dht.computeHeatIndex(temp, hum, false);
  smp_1 = analogRead(smp_a);
  smp_2 = analogRead(smp_b);
  smp_3 = analogRead(smp_c);

  moist = (smp_1 + smp_2 + smp_3) / 3;
  
  digitalWrite(verde, HIGH);
  delay(3000);

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

  digitalWrite(verde, HIGH);
  delay(3000);
}
// ------------------- Setup Function ------------------------- //
void setup() {
  Serial.begin(115200);
  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);

  initWifi();
  dht.begin();
}
// ------------------- Loop Function ------------------------- //
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    getDHTReads();
    EnvioDatos();
    delay(60000);
  }else {
     Serial.println("Error en la conexion WIFI");
  }
}
