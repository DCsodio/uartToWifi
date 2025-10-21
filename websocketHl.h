#ifndef WEBSOCKET_HANDLER_H
#define WEBSOCKET_HANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#define BUFFER_MAX 200 

extern uint8_t bufferSocketRx[BUFFER_MAX];
extern bool datoNuevo;
extern WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length);
 
 
#endif // WEBSOCKET_HANDLER_H

