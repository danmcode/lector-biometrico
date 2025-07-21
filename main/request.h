#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class RequestHttps{
    
    public:
    HTTPClient http;
    WiFiClient client;
    
    /*
     * Funcion para realizar el registro de los contactos 
     * recibe el ID que captura el lector biometrico
     * numero de la instancia
     * base de datos de la instancia
     * url de la API donde se conectara
     * 
     * @return JSON {"Tipo":"Entra || Sale", "Contacto":"nombre del contacto"}
    */
    String registerEntryAndExit(String idFingerPrint, String numberInstance, String dataBase, String apiUrl, String apikey ){
        
        String output;
        StaticJsonDocument<192> doc;
        
        doc["apikey"] = apikey;
        doc["idHuella"] = idFingerPrint;
        doc["instancia"] = numberInstance;
        doc["bd"] = dataBase;
        
        serializeJson(doc, output );
 
        //Verificar el estado del Wifi
        if( WiFi.status() == WL_CONNECTED ){

            http.begin( client, apiUrl );
            http.addHeader( "Content-Type", "Content-Type: application/json" );

            int httpResponse = http.POST(output);
            String httpJsonResponse = http.getString();

            return httpJsonResponse;
            
        }else { // No esta conectado al WiFi
          return "NO_CONECTED";
        }
    } //getContactFingerId

    /*
    * Realizar el registro de las huellas digitales.
    */
    String registerFingerId(String apikey, String cedula, int idHuella, String numberInstance, String db, String apiUrl){
        
        String output;
        StaticJsonDocument<192> doc;
        
        doc["apikey"] = apikey;
        doc["cedula"] = cedula;
        doc["idHuella"] = idHuella;
        doc["instancia"] = numberInstance;
        doc["bd"] = db;
        
        serializeJson(doc, output);

        Serial.println(output);
 
        //Verificar el estado del Wifi
        if( WiFi.status() == WL_CONNECTED ){

            http.begin( client, apiUrl );
            http.addHeader( "Content-Type", "Content-Type: application/json" );

            int httpResponse = http.POST(output);
            String httpJsonResponse = http.getString();

            return httpJsonResponse;
            
        }else { // No esta conectado al WiFi
          return "NO_CONECTED";
        }
    } 
 };
