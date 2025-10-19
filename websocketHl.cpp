#include "websocketHl.h"

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
    //Desconectado
			Serial.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED:
			Serial.printf("[WSc] Connected to url: %s\n", payload);

			//Envia mensaje al servidor
			webSocket.sendTXT("Connected");
			break;
		case WStype_TEXT:
      //recepcion de mensaje
			Serial.printf("[WSc] get text: %s\n", payload);
			break;

		case WStype_BIN:
			//aca recibe bytes
      Serial.printf("[WSc] get binary length: %u\n", length);

			break;
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
	}
}