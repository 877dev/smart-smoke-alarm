void heartbeat()  // function for heartbeat check and watchdog pat
{

  //First check for alarm situation

  if (digitalRead(smoke) == HIGH)
  {
    MQTTclient.publish((base_mqtt_topic + "/alarm").c_str(), String("true").c_str(), true);  //do not retain
    DEBUG_PRINTLN("Alarm detected");
  }
  else
  {
    MQTTclient.publish((base_mqtt_topic + "/alarm").c_str(), String("false").c_str(), true);
    DEBUG_PRINTLN("All ok");
  }


  //Read battery level
  int sensorValue = analogRead(A0); //read the A0 pin value
  float voltage = sensorValue * (10.00 / 1023.00); //convert the value to a true voltage, where 10V = 1024

  //Publish 9V battery level
  MQTTclient.publish((base_mqtt_topic + "/battery").c_str(), String(voltage).c_str(), true);
  DEBUG_PRINT("Battery is at ");
  DEBUG_PRINT(voltage);
  DEBUG_PRINTLN(" volts");



  //Publish freeram value 
  MQTTclient.publish((base_mqtt_topic + "/freeram").c_str(), String(ESP.getFreeHeap()).c_str(), true);


  //Publish heartbeat - comment out this line if using below watchdog code
  MQTTclient.publish((base_mqtt_topic + "/heartbeat").c_str(), String(WiFi.RSSI()).c_str(), true);


  //Optional watchdog function:
  //if mqtt message published successfully, pat the watchdog
  //if (MQTTclient.publish((base_mqtt_topic + "/heartbeat").c_str(), String(WiFi.RSSI()).c_str(), true))
  //{
  //Watchdog pat here
  //}


}
