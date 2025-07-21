#include <SPI.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "oled_screen.h"

class WiFiConfig{

  public:
  
  void connectToWiFi(const char *ssid, const char *password ){
    
    OledScreen oledScreen;

    oledScreen.printOledIconWiFiConfig();
    Serial.println("MAC: ");
    Serial.println(WiFi.macAddress());
    WiFi.mode(WIFI_OFF); 
    delay(1000);
    WiFi.mode(WIFI_STA);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Connected");
    oledScreen.printOledIconWiFiConfigDone();
    delay(1000);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

};
