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
Author

Saurav
