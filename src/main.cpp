/* main.cpp
 * This file contains demo code to test the ADS1299
 * 
 * Check configs.h file for configurations that can be set 
 * 
 * Authors: Mingye Chen
 */
#include <Arduino.h>
#include "ADS1299.h"
#include <SPI.h>
#include <pins_arduino.h>

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 2
bool streaming_enabled ;
ADS1299 ADS;

#define OPENBCI_DATA_BUFFER_SIZE 50

#define OPENBCI_NAME "OpenBCI-FFFF"
#define OPENBCI_VERSION "v2.0.5"

#define SOFT_AP_SSID "OpenBCI WiFi AP"
#define SOFT_AP_PASSWORD "abcd1234*"

#define JSON_BUFFER_SIZE 1024

uint8_t* tcp_transfer_buffer = NULL;

IPAddress local_ip(192, 168, 4, 1);
IPAddress network_gateway(192, 168, 4, 1);
IPAddress subnet_mask(255, 255, 255, 0);

WebServer web_server(80);
WiFiClient tcp_client;

size_t wifi_latency = 0;
// void setup() {
//   Serial.begin(115200);
//   Serial.println();
//   Serial.println("Serial starting");
//   /*
//   Pin connections:
//   SCK = 13
//   MISO (DOUT) = 12
//   MOSI (DIN) = 11
//   CS = 10; 
//   DRDY = 2;
//   */
//   ADS.setup(27,26,8,1);
//   //ADS.setup(9, 10); 
//   //ADS.setup(9,10,8,1);
//   ADS.STARTUP();
//   ADS.getID();
//   Serial.println("----------------------------------------------");
//   //PRINT ALL REGISTERS 
//   ADS.RREG(0x00, 0x17);
//   Serial.println("----------------------------------------------");
//   delay(2000);
// }

// void loop() {
//   #ifdef DATA_LOGGER_MODE
//   ADS.RDATA_logger();
//   //Serial.print("logger");
//   #else
//   ADS.RDATA_update();

//   //Serial.print("update");
//   #endif
// }


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Serial starting");
  /*
  Pin connections:
  SCK = 13
  MISO (DOUT) = 12
  MOSI (DIN) = 11
  CS = 10; 
  DRDY = 2;
  */
   ADS.setup(27,26,8,1);
   ADS.STARTUP();
   ADS.getID();
   Serial.println("----------------------------------------------");
   //PRINT ALL REGISTERS 
   ADS.RREG(0x00, 0x17);
   Serial.println("----------------------------------------------");

  ADS.RDATAC();
  
  //attachInterrupt(digitalPinToInterrupt(ADS1299_PIN_DRDY), ADS.drdy_interrupt,FALLING);
  attachInterrupt(digitalPinToInterrupt(ADS1299_PIN_DRDY), ads1299_drdy_interrupt, FALLING);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(SOFT_AP_SSID, SOFT_AP_PASSWORD);

  delay(250);
      
  WiFi.softAPConfig(local_ip, network_gateway, subnet_mask);
      
  delay(250);

  MDNS.begin("openbci");
    
  tcp_transfer_buffer = (uint8_t*)malloc(sizeof(openbci_data_packet));

  // web_server.on("/all", HTTP_GET, get_system_info);
  // web_server.on("/board", HTTP_GET, get_board_info);

  // web_server.on("/command", HTTP_POST, process_command);
    
  // web_server.on("/steam/start", HTTP_GET, start_streaming);
  // web_server.on("/steam/stop", HTTP_GET, start_streaming);

  // web_server.on("/output/raw", HTTP_GET, switch_raw_output);
  
  // web_server.on("/tcp", HTTP_GET, get_tcp_config);
  // web_server.on("/tcp", HTTP_POST, set_tcp_config);
  // web_server.on("/tcp", HTTP_DELETE, stop_tcp_connection);
  
  // web_server.onNotFound(invalid_request);
    
  MDNS.addService("http", "tcp", 80);
    
  web_server.begin();

  streaming_enabled=true ;
  delay(2000);
}
// void setup()
// {
//   // initialize LED digital pin as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
// }
void loop() {
  // #ifdef DATA_LOGGER_MODE
  // ADS.RDATA_logger();
  // //Serial.print("logger");
  // #else
  ADS.RDATA_update();

  //Serial.print("update");
  // #endif
}