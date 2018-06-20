#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "Constants.h" 

void setup() {
    // Serial.begin(115200); 
    // Serial.println();

    // WiFi.mode(WIFI_STA);
    // WiFi.disconnect();
    // delay(100);

    Serial.begin(115200);
    Serial.println();
    
    WiFi.begin(Constants::SSID, Constants::PASSWORD);
    
    Serial.print("Connecting...");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client;
    Serial.printf("\n[Connecting to %s ... ", Constants::HOST);
    if (client.connect(Constants::HOST, 80))
    {
        Serial.println("connected]");   
        Serial.println("[Sending a request]");
        client.print(String("GET /") + " HTTP/1.1\r\n" +
                     "Host: " + Constants::HOST + "\r\n" +
                     "Connection: close\r\n" +
                     "\r\n" );  
        Serial.println("[Response:]");
        while (client.connected()) {
            if (client.available()) {
              String line = client.readStringUntil('\n');
              Serial.println(line);
            }
        }
        client.stop();
        Serial.println("\n[Disconnected]");
    }
    else {
        Serial.println("connection failed!]");
        client.stop();
    }
    delay(5000);
}