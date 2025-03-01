#include <WiFi.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char *ssid = "pranpro";
const char *password = "cybozs73";

// Relay control pin
const int relayPin = 5; // Change to the GPIO you are using

WebServer server(80); // Web server on port 80

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Set up relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Start with relay off

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32 IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Define HTTP request handlers
  server.on("/relay/on", HTTP_GET, []() {
    digitalWrite(relayPin, HIGH);  // Turn relay ON
    server.send(200, "text/plain", "Relay is ON");
  });

  server.on("/relay/off", HTTP_GET, []() {
    digitalWrite(relayPin, LOW);  // Turn relay OFF
    server.send(200, "text/plain", "Relay is OFF");
  });

  // Start the server
  server.begin();
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests
}
