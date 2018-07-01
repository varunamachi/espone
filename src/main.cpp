#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <RestClient.h>

#include "Secrets.h" 

std::unique_ptr<RestClient> client = nullptr;
String response;
int status;

void login() {
    auto data = String{"{"} 
            + "entityID: " + Secrets::ENTITY_ID + ",\n" 
            + "owner: " + Secrets::ENTITY_OWNER + ",\n" 
            + "secret: " + Secrets::SECRET + "\n}";
    Serial.println(data);
    status = client->post("/sprw/api/v0/login", data.c_str(), &response);
    Serial.printf("Status: %d\n Response: %s\n", status, response.c_str());
}

void ping() {
    if (client != nullptr) {
        status = client->get("/sprw/api/v0/ping", &response);
        Serial.printf("Status: %d\n Response: %s\n", status, response.c_str());
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
    login();
} 

void loop() {
    if (Serial.read()) {
        ping();
    }
}