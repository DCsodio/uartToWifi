#include "protocoloPaquete.h"
#include "websocketHl.h"

#define TX_PIN 5
#define RX_PIN 4


//ETAPA DE CONEXION WIFI
//const char* ssid     = "Tenorio";
//const char* password = "juanita1";
const char* ssid     = "Senku-2.4Ghz";
const char* password = "Caroyeze";
//const char* ssid     = "Grupo Boldt Guest";
//const char* password = "01234567890!";

//const char* ssid     = "motog200";
//const char* password = "caro1234";
void setup() {
    //ETAPA UART
    Serial.begin(115200);
    Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);

    Serial.setDebugOutput(true);
    Serial.println();

    //ETAPA CONFIGURACION WIFI
    WiFi.begin(ssid, password);
    
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado");
    webSocket.begin("192.168.1.63", 12345, "/"); // Cambiá IP y puerto
    webSocket.onEvent(webSocketEvent); //colocamos la maquina de estados
    webSocket.setReconnectInterval(5000); //Tiempo de reconexion 5segundos
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.reconnect();
    }
    webSocket.loop();
    analizarPaquete();
    if(getNuevaLectura()){
        webSocket.sendBIN((uint8_t*)&pkt,sizeof(Paquete));
        nuevoPaquete=false;
        Serial.println("Paquete enviado por WebSocket (binario).");
    }
    if(datoNuevo){
        Serial1.write((const char*)bufferSocketRx,strlen((const char*)bufferSocketRx));
        datoNuevo=false;
        Serial.println("Datos de wifi enviados por uart al lpc845");
    }
}
