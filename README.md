ESP8266 DHT11 IoT Monitoring

An IoT-based temperature and humidity monitoring project using ESP8266 NodeMCU and a DHT11 sensor.

Sensor data is sent to ThingSpeak for remote monitoring and is also displayed on a local web dashboard hosted by the ESP8266.

Features
🌡️ Real-time temperature monitoring
💧 Real-time humidity monitoring
📡 Wi-Fi connectivity using ESP8266
☁️ ThingSpeak cloud monitoring
📱 Local web dashboard accessible from a phone
🔄 Automatic webpage refresh
📊 Temperature and humidity graphs on ThingSpeak
🟢 Sensor status display
Hardware Required
ESP8266 NodeMCU
DHT11 Temperature & Humidity Sensor
Jumper Wires
USB Cable
Wi-Fi Network
Circuit Connection
DHT11	ESP8266
VCC	3.3V
GND	GND
DATA	D4
Software & Libraries
Arduino IDE
ESP8266 Board Package
DHT Sensor Library by Adafruit
Adafruit Unified Sensor
ThingSpeak

The ESP8266 sends:

Field 1 → Temperature (°C)
Field 2 → Humidity (%)

The ThingSpeak channel can be configured as Public for remote viewing.

Local Web Dashboard

After connecting to Wi-Fi, the ESP8266 provides a local IP address.

Open that IP address in a phone or computer connected to the same Wi-Fi network to view the temperature and humidity dashboard.

Data Flow
DHT11 Sensor
     ↓
ESP8266 NodeMCU
     ↓
     Wi-Fi
   ↙       ↘
ThingSpeak   Local Web Dashboard
   ↓              ↓
Remote Data    Phone / PC

## Software & Setup

### 1. Arduino IDE

Download and install the official Arduino IDE:

https://www.arduino.cc/en/software

This project was developed using Arduino IDE 2.x.

### 2. ESP8266 Board Package

In Arduino IDE:

File → Preferences → Additional Boards Manager URLs

Add this official ESP8266 Boards Manager URL:

https://arduino.esp8266.com/stable/package_esp8266com_index.json

Then go to:

Tools → Board → Boards Manager

Search for:

ESP8266

Install:

ESP8266 by ESP8266 Community

After installation select:

NodeMCU 1.0 (ESP-12E Module)

Official ESP8266 installation documentation:
https://arduino-esp8266.readthedocs.io/en/latest/installing.html

### 3. Required Libraries

Install these libraries from:

Sketch → Include Library → Manage Libraries

#### DHT Sensor Library

Search:

DHT sensor library

Install:

DHT sensor library by Adafruit

Official repository:
https://github.com/adafruit/DHT-sensor-library

#### Adafruit Unified Sensor

Search:

Adafruit Unified Sensor

Install:

Adafruit Unified Sensor

This library is required by the Adafruit DHT Sensor Library.

Official repository:
https://github.com/adafruit/Adafruit_Sensor

### 4. Required Board

Board:

NodeMCU 1.0 (ESP-12E Module)

### 5. DHT11 Connection

| DHT11 | ESP8266 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | D4 |

### 6. Configuration

Before uploading the code, replace these placeholders with your own details:

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";

Do NOT upload real Wi-Fi passwords or API keys to a public GitHub repository.

### 7. ThingSpeak

Create a ThingSpeak channel with:

- Field 1 → Temperature (°C)
- Field 2 → Humidity (%)

The ESP8266 sends sensor readings to ThingSpeak every 20 seconds.

### 8. Local Dashboard

After connecting to Wi-Fi, open the IP address shown in the Serial Monitor.

Example:

http://192.168.x.x

The dashboard displays:

- Temperature
- Humidity
- Sensor status
- Wi-Fi status
- ESP8266 IP address
- Automatic refresh

Author:

Saurav
