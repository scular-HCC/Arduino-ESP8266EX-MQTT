# Arduino-ESP8266EX-MQTT
> A starter project for students: a minimal working Arduino + ESP8266 MQTT example to build on.

An Arduino Uno talks to an ESP8266EX Wi-Fi module using AT commands and connects to an MQTT broker. The sketch joins Wi-Fi, subscribes to `test/topic`, and publishes `Hello from Arduino!` to `test/topic` every 2 seconds. Incoming messages are printed to the Serial Monitor.

## Hardware
- Arduino Uno (or similar)
- ESP8266EX Wi-Fi module/board running AT firmware at 9600 baud
- An MQTT broker (the sketch is set to the public `broker.hivemq.com`, port 1883, no authentication)

## Wiring
| Arduino | ESP8266 |
|---|---|
| 3.3V (must supply 300-500 mA; an external regulator is likely needed) | VCC |
| GND | GND |
| 3.3V | CH_PD / EN |
| Pin 2 (software RX) | TX |
| Pin 3 (software TX) | RX (3.3 V logic; may need a level shifter) |

The Uno has only one hardware serial port, so the ESP8266 is on SoftwareSerial (pins 2 and 3).

## Libraries (Arduino Library Manager)
- PubSubClient (MQTT client)
- WiFiEspAT
- SoftwareSerial (included with the Arduino IDE)

## Build and run
1. Install the libraries above in the Arduino IDE.
2. Open `Arduino_ESP8266_AT_MQTT/Arduino_ESP8266_AT_MQTT.ino`.
3. Set `ssid` and `pass` to your Wi-Fi network. Change `mqtt_server` and `mqtt_port` if you are not using the public HiveMQ broker.
4. Select the Arduino board and port, then upload.
5. Open the Serial Monitor at **115200** baud. You should see "WiFi connected", then "Connecting to MQTT...connected".
6. Confirm messages from any MQTT client subscribed to `test/topic` (for example the HiveMQ web client or `mosquitto_sub -h broker.hivemq.com -t test/topic`).

## Notes
- The broker `broker.hivemq.com` is public: anyone can read and publish on `test/topic`.
- The sketch is configured for an unauthenticated, unencrypted connection (port 1883).
