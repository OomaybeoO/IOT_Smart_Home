#ifndef WIFIWEBSOCKET_H
#define WIFIWEBSOCKET_H

#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ArduinoJson.h>  
#include <Arduino.h>
#include <SP.h>

#define LED1 15
#define LED2 2
#define FAN1 0
#define FAN2 4
using namespace websockets;

extern WebsocketsClient* client;
void processMessage(float arg1);
void connectToWiFi(const char* ssid, const char* password);
bool connectToWebSocket(WebsocketsClient* client, const char* host, uint16_t port, const char* path);
void sendMessage(const char* user, const char* action_code, float arg1, float arg2, float arg3);
void handleWebSocketMessage(WebsocketsMessage message);
void checkConnection(void);
void ControlDevices(bool led1,bool led2,bool fan1,bool fan2);
#endif // WIFIWEBSOCKET_H