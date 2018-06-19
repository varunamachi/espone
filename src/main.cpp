#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}

void loop() {
    Serial.println("Scanning...");
    auto numFound = WiFi.scanNetworks();
    Serial.printf("Number of nw found: %d\n", numFound);
    for (int i = 0; i < numFound; ++ i ) {
        Serial.println(WiFi.SSID(i));
    }
    Serial.println();
    delay(3000);
}