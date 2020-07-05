//Debugging
#define DEBUG //  <--------------Enable disable debug serial prints - comment out this line only
#ifdef DEBUG
#define DEBUG_PRINT(x)      Serial.print (x)
#define DEBUG_PRINTLN(x)    Serial.println (x)
#define DEBUG_PRINTLNHEX(x) Serial.println (x, HEX)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTLNHEX(x)
#endif
//

//Libraries
#include <PubSubClient.h>  // https://github.com/knolleary/pubsubclient
#include <ESP8266WiFi.h>   // connection to WiFi and reconnect
//
#include <ESP8266mDNS.h>  //for OTA updates
#include <WiFiUdp.h>      //for OTA updates
#include <ArduinoOTA.h>   //for OTA updates
//
#include <SimpleTimer.h>  // for calling functions
//
//
//Secret credentials file - see notes tab for a template, or edit the code with your own details manually
#include <C:\arduino\secret_credentials.h>

//Login credentials
//Wifi
char ssid[] = mySSID;       //Enter your WIFI Name
char pass[] = myPASSWORD;   //Enter your WIFI Password
//ArduinoOTA
char ota_pass[] = myOTApassword; //Enter your Arduino OTA password here


const byte smoke = D5;      // input from smoke alarm (HIGH = smoke detected, LOW = all good)


//MQTT stuff******************************************************************************************************************************************************************
// MQTT Server Setting variables...
IPAddress mqtt_server_ip          myMqttIP;                      // Change to the IP Address for your MQTT Server...
const int mqtt_port =             myMqttPort;                    // Port for the MQTT Server...
const char *mqtt_username =       myMqttUser;                    // Change to your MQTT Server username...
const char *mqtt_password =       myMqttPassword;                // Change to your MQTT Server password...
String mqtt_client_id =           "smoke_alarm_v001";            // Used for unique MQTT Client ID
String base_mqtt_topic =          "octoPrint/smoke_alarm";       // Start of the MQTT Topic name used by this device
int mqtt_connect_count;                                          // Count of how may times we've connected to the MQTT server since booting (should always be 1 or more)
//
WiFiClient My_WiFi_Client;
PubSubClient MQTTclient(My_WiFi_Client);
//******************************************************************************************************************************************************************************


char *client_id = "smoke_alarm_v001"; // Used for OTA hostname - see if can combine with mqtt_client_id

//Setup variables for heartbeat
int interval = 2000;
unsigned long previousMillis = 0;



void setup()
{
  Serial.begin(74880);    // This is the native baud rate of most NodeMCUs, using this baud rate you will be able to see MCU and Debug messages in the serial monitor
  
  setup_wifi(); //connect to wifi and start OTA server

  //MQTT setup and connect
  MQTTclient.setServer(mqtt_server_ip, mqtt_port); //setup MQTT broker information as defined earlier
  MQTT_Connect();                                  //Connect to MQTT broker, publish Status/MAC/count, and subscribe to keypad topic

 pinMode(smoke, INPUT);                //set smoke pin as an input


}
