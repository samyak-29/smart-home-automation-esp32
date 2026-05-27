# 🏠 Smart Home Automation System
> ESP32-based real-time home automation with Bluetooth control, multi-sensor monitoring, and OLED display — built as part of B.Tech Minor Project at SRMIST (2025)

---

## 📌 Overview

A fully functional smart home system built on the **ESP32 microcontroller** that monitors environmental conditions in real time and allows wireless control of home appliances via a custom **Android Bluetooth app**. The system handles temperature/humidity sensing, smoke/gas detection, ambient light control, and motion detection — all running concurrently with live status shown on an OLED display.

---

## ✨ Features

| Feature | Sensor/Component | Behaviour |
|---|---|---|
| Temperature & Humidity Monitoring | DHT11 | Live readings on OLED display |
| Automatic Light Control | LDR (GPIO 26) | Light relay triggers when LDR ≥ 2200 |
| Smoke / Gas Detection | MQ-series (GPIO 27) | Buzzer + LED alert when value ≥ 3200 |
| Motion Detection | HC-SR04 Ultrasonic | LED alert when object within 20 cm |
| Appliance Control | Relay x2 (GPIO 4, 5) | Fan & light toggle via Bluetooth |
| OLED Dashboard | SSD1306 128x64 | Real-time status of all sensors |
| Wireless Control | Bluetooth SPP | Android app sends single-char commands |

---

## 🔧 Hardware

- **Microcontroller:** ESP32 (dual-core, 240 MHz)
- **Sensors:** DHT11, MQ-2 Gas Sensor, LDR, HC-SR04 Ultrasonic
- **Actuators:** 2x Relay Module (fan + light), Active Buzzer, Status LEDs
- **Display:** SSD1306 OLED 128x64 (I2C — SDA: GPIO 22, SCL: GPIO 23)
- **Communication:** Bluetooth Classic (SPP) via ESP32 built-in

### Pin Map

```
DHT11         → GPIO 33
LDR           → GPIO 26 (analog)
MQ Gas Sensor → GPIO 27 (analog)
Ultrasonic TRIG → GPIO 15
Ultrasonic ECHO → GPIO 2
Fan Relay     → GPIO 5
Light Relay   → GPIO 4
Smoke Buzzer  → GPIO 12
Smoke LED     → GPIO 19
Motion LED    → GPIO 18
OLED SDA      → GPIO 22
OLED SCL      → GPIO 23
```

---

## 📱 Android App

The companion Android app was built using **MIT App Inventor** and communicates over Bluetooth SPP. It sends single-character commands to the ESP32:

| Command Char | Action |
|---|---|
| `F` | Fan ON |
| `Y` | Fan OFF |
| `L` | Light ON |
| `Z` | Light OFF |
| `S` | Dismiss smoke alert |

The `.aia` source file is included in this repo — import it into [MIT App Inventor](https://appinventor.mit.edu) to modify or rebuild the app.

---

## 🚀 How to Flash

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:  
   `File → Preferences → Additional Board URLs:`  
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Install required libraries via Library Manager:
   - `DHT sensor library` (Adafruit)
   - `Adafruit SSD1306`
   - `Adafruit GFX`
   - `BluetoothSerial` (included with ESP32 core)
4. Open `smart_home_automation.ino`, select board **ESP32 Dev Module**, upload.

---

## 📊 System Architecture

```
┌─────────────────────────────────────────┐
│              ESP32 (240 MHz)            │
│                                         │
│  ┌──────────┐   ┌──────────────────┐   │
│  │ Sensors  │──▶│  Control Logic   │   │
│  │ DHT11    │   │  Thresholds      │   │
│  │ MQ Gas   │   │  LDR ≥ 2200      │   │
│  │ LDR      │   │  Smoke ≥ 3200    │   │
│  │ HC-SR04  │   │  Distance ≤ 20cm │   │
│  └──────────┘   └────────┬─────────┘   │
│                           │             │
│  ┌──────────┐   ┌─────────▼────────┐   │
│  │ BT App   │──▶│   Actuators      │   │
│  │ Android  │   │   Fan Relay      │   │
│  └──────────┘   │   Light Relay    │   │
│                 │   Buzzer / LEDs  │   │
│  ┌──────────┐   └──────────────────┘   │
│  │   OLED   │◀── Live status display   │
│  └──────────┘                          │
└─────────────────────────────────────────┘
```

---

## 📁 Repository Structure

```
smart-home-automation/
├── smart_home_automation.ino   # Main ESP32 firmware
├── smart_home_automation.aia   # MIT App Inventor source file
├── circuit_diagram.png         # Wiring diagram (add yours here)
├── demo/
│   └── demo_photo.jpg          # Hardware photo (add yours here)
└── README.md
```

---

## 🔬 Research Context

This project was developed as part of a Minor Project at **SRM Institute of Science and Technology** under the guidance of **Dr. Sarada V.** (Dept. of ECE). A companion Major Project on nanomaterial-based mercury ion sensing using functionalized rGO was submitted for publication to **IEEE Sensors Journal** (under review, 2026).

---

## 👤 Author

**Samyak Khatod**  
B.Tech, Electronics & Communication Engineering  
SRM Institute of Science and Technology, Kattankulathur  
📧 khatodsamyak50@gmail.com  
🔗 [LinkedIn](https://linkedin.com/in/samyak-khatod)

---

## 📄 License

MIT License — free to use, modify and distribute with attribution.
