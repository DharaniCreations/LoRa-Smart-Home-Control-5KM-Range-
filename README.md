📡 LoRa Smart Home Control (5KM Range)

A long-range smart home control system built using RYLR998 LoRa modules, NodeMCU ESP8266, and Arduino Uno.

This system supports:

✅ Online control using Blynk IoT

✅ Offline control using Touch Sensor

✅ 5KM long-range communication (LoRa 868MHz)

✅ Real-time acknowledgment system

✅ OLED & LCD status monitoring

🚀 Features

📡 868 MHz LoRa Communication

🔁 Bidirectional Communication with ACK

🌐 Blynk IoT Integration

📶 LoRa Link Status Monitoring

🖥 OLED Display (NodeMCU Side)

📟 16x2 LCD Display (Arduino Side)

🔌 Active-Low Relay Control

⚡ Online + Offline Operation

🧩 Hardware Used
Component	Quantity
NodeMCU ESP8266	1
Arduino Uno	1
RYLR998 LoRa Module	2
16x2 LCD (I2C)	1
OLED Display (SSD1306)	1
Relay Module (Active-Low)	1
Touch Sensor	1
Voltage Divider (2kΩ + 1kΩ)	1
🏗 System Architecture

NodeMCU (Transmitter Side)

Connects to WiFi

Communicates with Blynk App

Sends LoRa commands

Displays status on OLED

Arduino (Receiver Side)

Receives LoRa command

Controls relay

Sends acknowledgment

Displays status on LCD

🔌 Wiring Overview
NodeMCU Connections

LoRa TX → D7

LoRa RX → D8

Touch Sensor → D5

OLED SDA → D2

OLED SCL → D1

All powered using 3.3V.

Arduino Connections

LoRa TX → Pin 10

LoRa RX → Pin 11 (via voltage divider)

Relay IN → Pin 8

LCD SDA → A4

LCD SCL → A5

⚠️ LoRa RX must use a voltage divider (5V → 3.3V).

⚙️ LoRa Configuration (UART AT Commands)

Both modules must have:

AT+BAND=868000000
AT+NETWORKID=5


NodeMCU Side:

AT+ADDRESS=1


Arduino Side:

AT+ADDRESS=2


Baud Rate: 115200

📱 Blynk Setup

Create two datastreams:

Virtual Pin	Purpose
V0	Relay Control
V1	LoRa Link Status
🖥 Display Output
OLED (NodeMCU)

WiFi Status

LoRa Status

Command Source (Blynk / Touch)

Last Command Sent

LCD (Arduino)

LoRa Link Status

Relay State

📶 Range

LoRa communication tested up to 5KM range (line-of-sight conditions)
Actual range depends on:

Antenna quality

Environment

Obstacles

Transmission power

🎥 Demo Video

Watch full project demonstration here:

👉 [YouTube Video Link Here]

🌐 Reyax LoRa Module

Official Website:
https://reyax.com/

Module Used: RYLR998

🔮 Future Improvements

Multiple relay control

Sensor data transmission

Battery-powered remote nodes

LoRa mesh network

Web dashboard integration

👨‍💻 Author

Dharani Creations

If you found this project useful, consider giving a ⭐ on GitHub.
