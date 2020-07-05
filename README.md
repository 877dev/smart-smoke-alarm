# smart-smoke-alarm
Retrofit Fireangel smoke alarm with Wemos D1 mini

Hardware:
Wemos D1 mini
FireAngel SB1-TP-R Smoke Alarm
390K resistor
2 x 680K resistors

Description:
This takes a 'dumb' optical smoke alarm and adds MQTT capability, my usage is for my 3D printer connected with Octoprint.
If the detector notices smoke, it sends a MQTT message to the broker. Via node red this sends a MQTT message to a Sonoff S20 smart plug, killing the power.
Also via node red it notifies me via my phone (I use Blynk app, you can use whatever you want).

