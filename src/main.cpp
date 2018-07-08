#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <RestClient.h>
#include <ArduinoJson.h>

#include "Secrets.h"  

std::unique_ptr<RestClient> client = nullptr;
String response;
int status;
char authHeader[500] = "Authorization: Bearer ";

bool login() { 
    StaticJsonBuffer<2048> buffer;
    auto &obj = buffer.createObject();
    obj["entityID"] = Secrets::ENTITY_ID;
    obj["owner"] = Secrets::ENTITY_OWNER;
    obj["secret"] = Secrets::SECRET;
    String data;
    obj.printTo(data);
    Serial.println(data);
    status = client->post("/sprw/api/v0/entity/auth", data.c_str(), &response);
    bool result = false;
    if (status == 200) {
        auto &root = buffer.parseObject(response);
        const char * token = root["data"]["token"];
        strcat(authHeader, token);
        result = true;
    }
    Serial.printf("Status: %d\n\n Response: %s\n", status, response.c_str());
    return result;
} 

void setup() {
    Serial.begin(115200);
    Serial.println(); 
     
    WiFi.begin(Secrets::SSID, Secrets::PASSWORD);
    
    Serial.printf("Config: \n\tHost: %s "
        "\n\tPort: %d\n", Secrets::HOST, Secrets::PORT);
    Serial.println("Connecting...");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    if (Secrets::USE_SSL) {
        client = std::unique_ptr<RestClient>( new RestClient{ 
            Secrets::HOST, 
            Secrets::PORT, 
            Secrets::SSL_FP});
    } 
    else {
        client = std::unique_ptr<RestClient>( new RestClient{ 
            Secrets::HOST, 
            Secrets::PORT});
    }
    client->setContentType("application/json");
    login();
} 

void ping() {
    if (client != nullptr) {
        response = "";
        client->setHeader(authHeader);
        status = client->get("/sprw/api/v0/ping", &response);
        Serial.printf("Status: %d\n\n Response: %s\n\n", 
            status, 
            response.c_str());
    } else {
        Serial.println("Invalid client configuration"); 
    }
    delay(5000); 
}

void loop() {
    auto av = Serial.readString();
    if (av.length() != 0) {
        if (av.startsWith("ping")) {
            ping();
        }
    }
    delay(100);
}