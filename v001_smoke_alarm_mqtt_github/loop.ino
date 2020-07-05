void loop ()
{

  // Add support for OTA***************************************
  ArduinoOTA.handle();
  // **********************************************************

  //MQTT processing
  if (!MQTTclient.connected())     // Note that MQTTclient.connected() will still return 'true' until the MQTT keepalive timeout has expired (around 35 seconds for my setup)
  {
    MQTT_Connect();
  }
  else
  {
    MQTTclient.loop();


    //If connection to MQTT ok, check the time
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis > interval)
    {
      //Time to call the function
      previousMillis = currentMillis;
      heartbeat();
    }

  }
  
}
