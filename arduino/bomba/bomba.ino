#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

// ------------------- Wifi ------------------------- //
// const char* ssid = "Megacable-2FC0";
// const char* password = "nhJn3XY4VL";

const char* ssid = "207_C";
const char* password = "ISC2024/";

const char* serverName = "pied-test.000webhostapp.com/esp-outputs-action.php?action=outputs_state&board=1";

// ------------------- Variables ------------------------- //
const long interval = 3000;
unsigned long previousMillis = 0;

String outputsState;
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
// ------------------- Funcion GET Bomba ------------------------- //
String httpGETRequest(const char* serverName) {
     WiFiClientSecure *client = new WiFiClientSecure;
  
   client->setInsecure();
   HTTPClient https;
    
   https.begin(*client, serverName);
  
   int httpResponseCode = https.GET();
  
   String payload = "{}"; 
  
   if (httpResponseCode>0) {
//     Serial.print("HTTP Response code: ");
//     Serial.println(httpResponseCode);
        payload = https.getString();
   }
//   else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
  https.end();
  return payload;
}

void setup() {
  Serial.begin(115200);
  initWifi();
}
// ------------------- Loop Function ------------------------- //
void loop() {
  if(WiFi.status() == WL_CONNECTED){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= interval) {
       outputsState = httpGETRequest(serverName);
//       Serial.println(outputsState);
       JSONVar myObject = JSON.parse(outputsState);

       if (JSON.typeof(myObject) == "undefined") {
//         Serial.println("Parsing input failed!");
         return;
       }    
       JSONVar keys = myObject.keys();
    
       for (int i = 0; i < keys.length(); i++) {
         JSONVar value = myObject[keys[i]];
         pinMode(atoi(keys[i]), OUTPUT);
         digitalWrite(atoi(keys[i]), atoi(value));
      }
     previousMillis = currentMillis;
   }
    
  }else {
     Serial.println("Error en la conexion WIFI");
  }
}