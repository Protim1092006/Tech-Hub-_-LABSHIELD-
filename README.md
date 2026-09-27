# Tech-Hub-_-LABSHIELD-
LabShield is a low-cost ESP32-based smart laboratory safety system that monitors temperature and gas/smoke levels in real time. It uses sensors, an OLED display, LEDs, and a buzzer to detect potential hazards and provide immediate visual and audible warnings. The prototype is developed and tested using Wokwi.
# LabShield 🛡️

## Smart Laboratory Safety Monitoring System

LabShield is a low-cost ESP32-based smart laboratory safety system designed to monitor environmental conditions and provide early hazard warnings.

## Features

- 🌡️ Real-time temperature monitoring
- 💨 Gas/smoke monitoring
- 🖥️ OLED real-time status display
- 🟢 Normal condition indication
- 🟡 Caution warning
- 🔴 High-risk/emergency warning
- 🔊 Audible emergency alert
- 📊 Multi-sensor risk assessment
- 🧪 Wokwi-based prototype

## Hardware

- ESP32 DevKit
- DHT22 Temperature & Humidity Sensor
- MQ-2 Gas/Smoke Sensor
- SSD1306 OLED Display
- Green LED
- Yellow LED
- Red LED
- Buzzer
- 220Ω Resistors

## Pin Configuration

| Component | ESP32 Pin |
|---|---|
| DHT22 DATA | GPIO 4 |
| MQ-2 AO | GPIO 34 |
| MQ-2 DO | GPIO 33 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| Green LED | GPIO 14 |
| Yellow LED | GPIO 27 |
| Red LED | GPIO 26 |
| Buzzer | GPIO 25 |

## Working

The ESP32 collects temperature and gas/smoke readings from the sensors. The readings are processed using predefined safety thresholds. Based on the combined sensor conditions, the system displays the current status and activates the appropriate LED and audible warning.

## Prototype

The prototype is designed and tested using Wokwi.

## Future Improvements

- Wi-Fi-based remote monitoring
- Web dashboard
- Emergency notifications
- Additional environmental sensors
- Data logging
- Physical hardware implementation

## Project Goal

To demonstrate an affordable embedded safety system capable of providing early warnings for potentially hazardous laboratory conditions.
