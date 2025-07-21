#include <Adafruit_Fingerprint.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Hash.h>
#include <SPI.h>
#include <SocketIOclient.h>
#include <SoftwareSerial.h>
#include <WebSocketsClient.h>

#include "config.h"
#include "oled_screen.h"
#include "request.h"
#include "wifi_config.h"

#define Finger_Rx 14 // Pin D5
#define Finger_Tx 12 // Pin D6
SoftwareSerial mySerial(Finger_Rx, Finger_Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

SocketIOclient socketIO;
WiFiConfig conn;
OledScreen oledScreen;
RequestHttps request;

// Pin de salida del Relay
int relayInput = 2;

unsigned long messageTimestamp = 0;

void socketIOEvent(socketIOmessageType_t type, uint8_t* payload, size_t length)
{
    String qtu = String((char*)payload);
    switch (type) {
    case sIOtype_DISCONNECT: {
        Serial.printf("[IOc] Disconnected!\n");
    } break;

    case sIOtype_CONNECT:
        Serial.printf("[IOc] Connected to url: %s\n", payload);
        break;

    case sIOtype_EVENT: {

        StaticJsonDocument<384> doc;

        Serial.println(qtu);

        DeserializationError error = deserializeJson(doc, qtu);

        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }

        const char* identification = doc["identification"]; // "1127076645"
        const char* instance = doc["instance"]; // "2147483647"
        const char* dataBase = doc["dataBase"]; // "proteccion_enlinea"
        const char* name = doc["name"]; // "ALEJANDRO"
        const char* lastName = doc["lastName"]; // "CAMILO RESTREPO"
        const char* userId = doc["userId"]; // "124394"
        int biometricId = doc["biometricId"]; // 64
        const char* type = doc["type"]; // "registro"
    } break;
    }
}

void setup()
{
    Serial.begin(115200);
    conn.connectToWiFi(WIFI_SSID, WIFI_PASSWORD); // Llama al metodo que conecta el wifi

    oledScreen.printOledIconNoFingerDetected();

    Serial.setDebugOutput(true);
    socketIO.begin(SOCKET_SERVER, SOCKET_PORT);
    socketIO.onEvent(socketIOEvent);

    oledScreen.printOledIconNoFingerDetected();

    // Pin de salida
    pinMode(relayInput, OUTPUT);
}

void loop()
{
    //  Empty();
    socketIO.loop();
}

// Enviar los mensajes a traves del socket
void sendSocketMessage(String evt, String type, String person)
{
    uint64_t now = millis();

    if (now - messageTimestamp > 2000) {
        messageTimestamp = now;

        DynamicJsonDocument doc(1024);
        JsonArray array = doc.to<JsonArray>();

        array.add(evt);
        JsonObject param1 = array.createNestedObject();
        param1["type"] = type;
        param1["person"] = person;

        String output;
        serializeJson(doc, output);
        Serial.print(output);
        socketIO.sendEVENT(output);
    }
}
