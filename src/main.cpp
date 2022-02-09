#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include "WebFiles.h"
#include "Pixel.h"

const char* ssid = "Telia-64E6A5-Greitas";
const char* password = "71C2911760";

ESP8266WebServer server(80);
Pixel led(D2, D1, D0);

unsigned long timestamp = 0;
Color color = { 255, 0, 0 };

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    switch (server.method())
    {
    case HTTP_ANY:
        message += "ANY";
        break;
    case HTTP_GET:
        message += "GET";
        break;
    case HTTP_HEAD:
        message += "HEAD";
        break;
    case HTTP_POST:
        message += "POST";
        break;
    case HTTP_PUT:
        message += "PUT";
        break;
    case HTTP_PATCH:
        message += "PATCH";
        break;
    case HTTP_DELETE:
        message += "DELETE";
        break;
    case HTTP_OPTIONS:
        message += "OPTIONS";
        break;
    default:
        message += "-";
        break;
    }
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    
    for (uint8_t i = 0; i < server.args(); i++)
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    
    server.send(404, "text/plain", message);
}

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    if (MDNS.begin("esp8266"))
        Serial.println("MDNS responder started");
    
    server.on("/", []() { 
        server.send(200, "text/html", WebFiles::slider_picker_html);
    });

    server.on("/slider_picker.html", []() { 
        server.send(200, "text/html", WebFiles::slider_picker_html);
    });
    server.on("/slider.css", []() { 
        server.send(200, "text/css", WebFiles::slider_css);
    });
    server.on("/main.js", []() { 
        server.send(200, "text/js", WebFiles::main_js);
    });

    server.on("/led/get", []() {
        char buf[128];
        sprintf(buf, "{\"red\":%u,\"green\":%u,\"blue\":%u}", color.r, color.g, color.b);
        server.send(200, "application/json", buf);
    });

    server.on("/led/set", []() {
        DynamicJsonDocument doc(1024);
        auto err = deserializeJson(doc, server.arg(0));

        Serial.println(err.c_str());

        color.r = doc["red"];
        color.g = doc["green"];
        color.b = doc["blue"];
    });

    server.onNotFound(handleNotFound);
    
    server.begin();
    Serial.println("HTTP server started");
}

void loop() 
{
    server.handleClient();
    
    if (millis() - timestamp >= 50)
    {
        led.Write(color);
        
        timestamp = millis();
    }
}