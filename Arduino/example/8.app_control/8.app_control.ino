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
#define SPEED_PIN_LEFT    26
#define SPEED_PIN_RIGHT    25
hw_timer_t * timer = NULL; 
volatile uint8_t left_Counter = 0;
volatile uint8_t right_Counter = 0;
int counter = 0;

DynamicJsonDocument doc_send(1024);
DynamicJsonDocument doc_recv(1024);

String temp_send;

//String output;
bool led_status = false;


/***********************************************************
 * Functions
 */
void on_left_Pin()
{
  left_Counter++;
}
void on_right_Pin()
{
  right_Counter++;
}
void IRAM_ATTR onTimer(){
  counter = (left_Counter + right_Counter);
  left_Counter = 0;
  right_Counter = 0;
}

// Callback: receiving any WebSocket message
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
        webSocket.sendTXT(client_num, temp_send);
      }
      break;

    case WStype_TEXT:
      // Print out raw message
//      Serial.printf("[%u] Received text: %s\n", client_num, payload);
      //Analyze and process the received data
      deserializeJson(doc_recv, payload);
      if(doc_recv["M_region"]) 
      {
        if(! led_status)
        {
          car.set_light_color(50,100,10);
          led_status = true;
        }
      }
      else 
      {
        if(led_status)
        {
          car.set_light_off();
          led_status = false;
        }
      }
      car.move(doc_recv["K_region"], doc_recv["H_region"]);
      //Get the data assignment JSON object ,convert it into a string and send it to app 
      deserializeJson(doc_send, temp_send);  
      doc_send["A_region"] = get_speed();  
      car.get_angle_distance();
      doc_send["D_region"][0] = car.angle_distance[0]; 
      doc_send["D_region"][1] = car.angle_distance[1];   
      car.get_grayscale();
      for(int i = 0; i < 3; i++)
      {
          doc_send["L_region"][i] = car.adc_value[i];
      }
      serializeJson(doc_send, output);
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



/***********************************************************
 * Main
 */

void setup() {
  // the string in the input  will be duplicated in the JsonDocument.
//  char temp_data[300]; 
  String stringone = "{\'Name\':\"";
  String stringtwo = "\", \'Type\':\"ESP-4WD Car\", \'Check\':\"SunFounder Controller\"}";
  temp_send = stringone + String(AP_NAME) + stringtwo;
  
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
      
  pinMode(SPEED_PIN_LEFT, INPUT);
  attachInterrupt(SPEED_PIN_LEFT, on_left_Pin, RISING);
  pinMode(SPEED_PIN_RIGHT, INPUT);
  attachInterrupt(SPEED_PIN_RIGHT, on_right_Pin, RISING);
  // Set 80 divider for prescaler (see ESP32 Technical Reference Manual for more
  // info).
  timer = timerBegin(2, 80, true);

  // Attach onTimer function to our timer.
  timerAttachInterrupt(timer, &onTimer, true);

  // Set alarm to call onTimer function every second (value in microseconds).
  // Repeat the alarm (third parameter)
  timerAlarmWrite(timer, 1000000, true);

  // Start an alarm
  timerAlarmEnable(timer);

//   Start WebSocket server and assign callback
  webSocket.begin(); 
  webSocket.onEvent(onWebSocketEvent);

}

void loop() 
{
  webSocket.loop();
}
float get_speed()
{
  float value = 0;
  value = float(counter) / 2.0 / 20.0 * 2.0 * 3.14 * 3.3;
  return value;
 }

 
