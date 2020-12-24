#include "ESP32_RDP.h"
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#define AP_NAME "ESP-4WD Car"
#define AP_PASSWORD "123456789"
#define STA_NAME "MakerStarsHall"
#define STA_PASSWORD "sunfounder"
#define SWITCH_MODE "ap"

ESP32car car;

// Globals
//AsyncWebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(8765);

DynamicJsonDocument doc_send(1024);
DynamicJsonDocument doc_recv(1024);

char temp_recv[300];
char temp_send[300];
String temp_data;


void onWebSocketEvent(uint8_t client_num,
                      WStype_t type,
                      uint8_t * payload,
                      size_t length) {
   char output[300];
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
        webSocket.sendTXT(client_num, temp_data);
      }
      break;

    case WStype_TEXT:

      /***RECEVICE***/
      /*** print the message which received from controller ***/
      if(strcmp((char * )payload, temp_recv) != 0) 
      {
        memset(temp_recv, 0, 300);
        Serial.printf(" Received text: %s\n", payload);
        memcpy(temp_recv, (char *)payload, strlen((char *)payload));
      }
      /***the statement which trasfer String to JSon Objection***/
      deserializeJson(doc_recv, payload);   
      //   coding the control function here.

   
      /***SEND***/
      //   coding the sensor function here.
      /***** this code is the example for you test the message which you send to controller ****/
//       car.get_grayscale();
//       for(int i = 0; i < 3; i++)
//       {
//           doc_send["L_region"][i] = car.adc_value[i];
//       }
      
      /***the statement which trasfer JSon Objection to String***/
      serializeJson(doc_send, output);

      /*** print the message which send to controller ***/
      if(strcmp(output, temp_send) != 0) 
      {
        memset(temp_send, 0, 300);
        Serial.printf(" Send text: %s\n", output);
        memcpy(temp_send, output, strlen(output));
      }
      
      /*** send message to controller ***/
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
  temp_data = stringone + String(AP_NAME) + stringtwo;
  deserializeJson(doc_send, temp_data);
  Serial.begin(115200);

  if(SWITCH_MODE == "ap")
  {
      // Start access point
      WiFi.softAP(AP_NAME, AP_PASSWORD);
      // Print our IP address 
      Serial.println();
      Serial.println("AP running");
      Serial.print("My IP address: ");
      Serial.println(WiFi.softAPIP());   
  }
  else if(SWITCH_MODE == "sta")
  {
      // Connect to access point
      Serial.println("Connecting");
      WiFi.begin(STA_NAME, STA_PASSWORD);
      while ( WiFi.status() != WL_CONNECTED ) {
        delay(500);
        Serial.print(".");
      }
    
      // Print our IP address
      Serial.println("Connected!");
      Serial.print("My IP address: ");
      Serial.println(WiFi.localIP());
  }
  webSocket.begin(); 
  webSocket.onEvent(onWebSocketEvent);

}

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();

}
