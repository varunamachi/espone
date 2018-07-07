#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <RestClient.h>
#include <ArduinoJson.h>

#include "Secrets.h"  

std::unique_ptr<RestClient> client = nullptr;
String response;
int status;
StaticJsonBuffer<500> buffer;

bool login() { 
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
        Serial.println(token);
        auto hdr = String("Authorization: Bearer ") + token;
        client->setHeader(hdr.c_str());
        client->setHeader(Secrets::HOST_INFO);
        result = true;
    }
    Serial.printf("Status: %d\n\n Response: %s\n", status, response.c_str());
    return result;
} 

void ping() {
    if (client != nullptr) {
        response = "";
        status = client->get("/sprw/api/v0/ping", &response);
        Serial.printf("Status: %d\n\n Response: %s\n\n", 
            status, 
            response.c_str());
    } else {
        Serial.println("Invalid client configuration"); 
    }
    delay(5000); 
}

void setup() {
    Serial.begin(115200);
    Serial.println(); 
     
    WiFi.begin(Secrets::SSID, Secrets::PASSWORD);
    
    Serial.printf("Config: \n\tHost: %s "
        "\n\tPort: %d", Secrets::HOST, Secrets::PORT);
    Serial.print("Connecting...");
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

void loop() {
    auto av = Serial.available();
    if (av != 0) {
        for (auto i = 0; i < av; ++ i) {
            Serial.read();
        }
        ping();
    }
}