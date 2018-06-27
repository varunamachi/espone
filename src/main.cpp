#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <RestClient.h>

#include "Secrets.h" 

 std::unique_ptr<RestClient> client = nullptr;

void setup() {
    // Serial.begin(115200); 
    // Serial.println();

    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();
    // delay(100);

    Serial.begin(115200);
    Serial.println();
     
    WiFi.begin(Secrets::SSID, Secrets::PASSWORD);
    
    Serial.print("Connecting...");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
    client = std::unique_ptr<RestClient>( new RestClient{ 
        Secrets::HOST, 
        443, 
        Secrets::SSL_FP});
}

void loop() {
    if (client != nullptr) {
        String resp;
        client->get("sprw/api/v0/login", &resp);
    }
}