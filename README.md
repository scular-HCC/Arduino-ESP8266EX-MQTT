# Arduino-ESP8266EX-MQTT
Arduino sends commands to ESP8266EX (Wi-Fi module) to MQTT Broker


- Arduino — your main microcontroller running the logic.
- ESP8266EX Wi‑Fi module/board — provides Wi‑Fi connectivity and acts as the network interface.
- MQTT broker — e.g., Mosquitto, HiveMQ, Adafruit IO, or a local broker on your network.


Wiring
Arduino ---> ESP8266 Board
3.3V (must supply 300-500 mA try but likely need external regulator) ---> VCC
GND ---> GND
3.3 V ---> CH_PD / Enable
RX software (pin 2) ---> TX
TX software (pin 3) ---> RX (make sure 3.3 V may require level shift)


Libraries
PubSubClient (MQTT Client)
WiFiEspAT
SoftwareSerial



Note:  Uno's only support serial so need to use softwareserial
