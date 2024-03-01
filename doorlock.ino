#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define relay1 5  

const char* ssid = "ESP32_AP";
const char* password = "12345678";

AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);
   
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW); 
  delay(1000);  
  Serial.println("Initial state set to LOCKED");

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<form action=\"/unlock\"><input type=\"submit\" value=\"Unlock\"></form><form action=\"/lock\"><input type=\"submit\" value=\"Lock\"></form>");
  });

  server.on("/unlock", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(relay1, LOW);  
    delay(1000);  
    Serial.println("Unlocking...");
    request->send(200, "text/plain", "Unlocked");
  });

  server.on("/lock", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(relay1, HIGH);  
    delay(1000);  
    Serial.println("Locking...");
    request->send(200, "text/plain", "Locked");
  });

  server.begin();
}

void loop(){}
