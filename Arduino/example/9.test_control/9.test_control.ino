#include "ESP32_RDP.h"
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#define NAME "ESP-4WD Car"

// Constants
const char *ssid = NAME;
const char *password =  "123456789";

ESP32car car;

// Globals
//AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(8765);

DynamicJsonDocument doc_send(1024);
DynamicJsonDocument doc_recv(1024);

char temp_data[300];


void onWebSocketEvent(uint8_t client_num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {
   String output;
  // Figure out the type of WebSocket event
  switch(type) {

    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", client_num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("[%u] Connection from ", client_num);
        Serial.println(ip.toString());
        serializeJson(doc_send, output);
        webSocket.sendTXT(client_num, output);
      }
      break;

    case WStype_TEXT:
      // Print out raw message
//      Serial.printf("[%u] Received text: %s\n", client_num, payload);
      
      if(strcmp((char * )payload, temp_data) != 0) 
      {
        memset(temp_data, 0, 300);
        Serial.printf(" Received text: %s\n", payload);
        memcpy(temp_data, (char *)payload, strlen((char *)payload));
      }
      
      
     
      car.get_grayscale();
      for(int i = 0; i < 3; i++)
      {
          doc_send["L_region"][i] = car.adc_value[i];
      }
      serializeJson(doc_send, output);
//      Serial.println(output);
      webSocket.sendTXT(client_num, output);     
      break;

    // For everything else: do nothing
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:
      break;
    
  }
}


void setup() {
  // put your setup code here, to run once:
   String stringone = "{\'Name\':\"";
  String stringtwo = "\", \'Type\':\"ESP-4WD Car\", \'Check\':\"SunFounder Controller\"}";
  String temp_data;
  temp_data = stringone + String(NAME) + stringtwo;
  deserializeJson(doc_send, temp_data);

  Serial.begin(115200);

  // Start access point
  WiFi.softAP(ssid, password);

  // Print our IP address 
  Serial.println();
  Serial.println("AP running");
  Serial.print("My IP address: ");
  Serial.println(WiFi.softAPIP());
  webSocket.begin(); 
  webSocket.onEvent(onWebSocketEvent);

}

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();

}
