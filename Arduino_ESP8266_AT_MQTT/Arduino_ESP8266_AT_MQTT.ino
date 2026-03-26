#include <SoftwareSerial.h>     // Needed to create serial port using any Arduino pin
#include <WiFiEspAT.h>     // WiFi for the ESP8266 chip
#include <PubSubClient.h>     // Simple MQTT client

SoftwareSerial espSerial(2, 3);  // Creates software port named espSerial for RX, TX on pins 2 and 3

char ssid[] = "EXAMSOFT";     // Enter WiFi name
char pass[] = "";     // Enter WiFi password

char mqtt_server[] = "broker.hivemq.com";  // MQTT broker address
int mqtt_port = 1883;     // MQTT port number

WiFiClient espClient;     // Creates WiFiClient object that represents TCP client using ESP8266 WiFi connection
PubSubClient client(espClient);     // Creates MQTT client named client that using the espClient as TCP connection


/******* MQTT Callback Function *******/

void callback(char* topic, byte* payload, unsigned int length) {     // Defines function that will be called when a subscribed MQTT message arrives.  It receives the Topic, Payload bytes, and Payload length
  Serial.print("Message arrived: ");     // Prints label to the USB serial monitor
  Serial.println(topic);     // Prints the topic of incoming message
}

/******* Setup Function *******/

void setup() {     // Setup function only runs once on boot
  Serial.begin(115200);     // USB serial main hardware serial baud rate
  espSerial.begin(9600);    // ESP8266 AT baud rate (often 9600) Must match ESP8266 AT firmware baud rate

  WiFi.init(&espSerial);     // Tells the WiFiESPAT library to use espSerial

  Serial.println("Connecting to WiFi...");     // Printes status message
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {     // Loop tries to connect to WiFi.  Keeps trying until response is WL_Connected.
    delay(500);     // Waits 500 ms before trying again.
    Serial.print(".");     // Prints a dot each attempt to monitor progress.
  }
  Serial.println("\nWiFi connected");     // Prints WiFi connected on a newline.

  client.setServer(mqtt_server, mqtt_port);     // Configures the MQTT client with broker address and port.
  client.setCallback(callback);     // Registers the callback function so ti will be called whenever a subscribed MQTT message is received.

  reconnect();     // Calls the reconnect() function to establish the initial MQTT connection and subscribe to topics.
}

/******* Defines Reconnect Function to Help make sure connected to MQTT Broker*******/ 

void reconnect() {
  while (!client.connected()) {     // Loops as long as MQTT Client is not connected.
    Serial.print("Connecting to MQTT...");     // Prints status message.
    if (client.connect("arduinoClient")) {     // Tries to connect to MQTT Broker with the client ID arduinoClient.  Returns true if successful.
      Serial.println("connected");      // If the connection succeceds prints the confirmation.
      client.subscribe("test/topic");     // Suscribes to the MQTT Topic test/topic.  The incoming messages on that topic will trigger callback()
    } else {
      Serial.print("failed, rc=");     // Prints failure message.
      Serial.println(client.state());      // Prints the MQTT client state code
      delay(2000);      // Waits 2 seconds before trying again
    }
  }
}

/******* Loop function runs continuously after setup *******/

void loop() {
  if (!client.connected()) {     //Checks if the MQTT client is currently disconnected
    reconnect();      // If disconnected calls reconnect() to re-establish MQTT connection
  }
  client.loop();     // Processes incoming MQTT packets and keeps connection alive.  Needs to be frequently called.

  client.publish("test/topic", "Hello from Arduino!");     // Publishes the string to the test/topic on the MQTT broker.
  delay(2000);     // Waits 2 seconds
}