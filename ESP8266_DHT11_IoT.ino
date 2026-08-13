#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// -------- Wi-Fi Details --------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// -------- ThingSpeak Details --------
const char* apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";
const char* thingSpeakHost = "api.thingspeak.com";

// -------- DHT11 --------
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// -------- Local Web Server --------
ESP8266WebServer server(80);

float temperature = 0;
float humidity = 0;

bool sensorOK = false;

unsigned long lastThingSpeakUpdate = 0;
const unsigned long updateInterval = 20000;


// -------- Local Webpage --------
void handleRoot() {

  String page = "<!DOCTYPE html>";
  page += "<html>";
  page += "<head>";

  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<meta http-equiv='refresh' content='5'>";

  page += "<title>ESP8266 IoT Dashboard</title>";

  page += "<style>";

  page += "body {";
  page += "font-family: Arial, sans-serif;";
  page += "background: #f2f5f8;";
  page += "text-align: center;";
  page += "margin: 0;";
  page += "padding: 20px;";
  page += "}";

  page += ".container {";
  page += "max-width: 500px;";
  page += "margin: auto;";
  page += "}";

  page += "h1 {";
  page += "color: #222;";
  page += "}";

  page += ".card {";
  page += "background: white;";
  page += "padding: 25px;";
  page += "margin: 15px 0;";
  page += "border-radius: 15px;";
  page += "box-shadow: 0 4px 12px rgba(0,0,0,0.12);";
  page += "}";

  page += ".value {";
  page += "font-size: 42px;";
  page += "font-weight: bold;";
  page += "margin: 10px;";
  page += "}";

  page += ".label {";
  page += "font-size: 20px;";
  page += "color: #555;";
  page += "}";

  page += ".status {";
  page += "font-size: 18px;";
  page += "font-weight: bold;";
  page += "}";

  page += ".info {";
  page += "font-size: 15px;";
  page += "color: #555;";
  page += "}";

  page += "</style>";

  page += "</head>";

  page += "<body>";

  page += "<div class='container'>";

  page += "<h1>ESP8266 IoT Dashboard</h1>";

  // Temperature
  page += "<div class='card'>";
  page += "<div class='label'>Temperature</div>";
  page += "<div class='value'>";
  page += String(temperature, 1);
  page += " &deg;C";
  page += "</div>";
  page += "</div>";

  // Humidity
  page += "<div class='card'>";
  page += "<div class='label'>Humidity</div>";
  page += "<div class='value'>";
  page += String(humidity, 1);
  page += " %";
  page += "</div>";
  page += "</div>";

  // Sensor Status
  page += "<div class='card'>";
  page += "<div class='label'>Sensor Status</div>";

  if (sensorOK) {
    page += "<div class='status'>Sensor Working</div>";
  } else {
    page += "<div class='status'>Sensor Error</div>";
  }

  page += "</div>";

  // Device information
  page += "<div class='card'>";
  page += "<div class='label'>Device Information</div>";

  page += "<p class='info'>Wi-Fi: Connected</p>";

  page += "<p class='info'>IP Address: ";
  page += WiFi.localIP().toString();
  page += "</p>";

  page += "<p class='info'>Auto Refresh: 5 seconds</p>";

  page += "</div>";

  page += "<p class='info'>ESP8266 + DHT11</p>";

  page += "</div>";

  page += "</body>";
  page += "</html>";

  server.send(200, "text/html", page);
}


// -------- Send Data to ThingSpeak --------
void sendToThingSpeak() {

  WiFiClient client;

  if (!client.connect(thingSpeakHost, 80)) {

    Serial.println("ThingSpeak connection failed");

    return;
  }

  String url = "/update?api_key=";
  url += apiKey;

  url += "&field1=";
  url += String(temperature, 1);

  url += "&field2=";
  url += String(humidity, 1);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + thingSpeakHost + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("Data sent to ThingSpeak");

  delay(100);

  client.stop();
}


// -------- SETUP --------
void setup() {

  Serial.begin(115200);

  dht.begin();

  // Connect Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("Wi-Fi Connected!");

  Serial.print("ESP8266 IP Address: ");

  Serial.println(WiFi.localIP());


  // Start Local Web Server
  server.on("/", handleRoot);

  server.begin();

  Serial.println("Local web server started");
}


// -------- LOOP --------
void loop() {

  server.handleClient();


  // Read DHT11
  temperature = dht.readTemperature();

  humidity = dht.readHumidity();


  // Check sensor
  if (isnan(temperature) || isnan(humidity)) {

    sensorOK = false;

    Serial.println("Failed to read DHT11!");

    delay(2000);

    return;
  }

  sensorOK = true;


  // Serial Monitor
  Serial.print("Temperature: ");

  Serial.print(temperature);

  Serial.print(" °C | Humidity: ");

  Serial.print(humidity);

  Serial.println(" %");


  // ThingSpeak Update
  if (millis() - lastThingSpeakUpdate >= updateInterval) {

    sendToThingSpeak();

    lastThingSpeakUpdate = millis();
  }


  delay(2000);
}
