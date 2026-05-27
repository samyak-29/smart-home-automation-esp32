# 🔌 ESP32 Smart Home — Wiring Guide

Complete step-by-step wiring instructions using a **split power setup**:
- ESP32 powered via USB from laptop
- **3.3V** from ESP32 for low-voltage components (DHT11, LDR, OLED, Bluetooth)
- **5V from LM2596 buck converter** for higher-voltage components (Relay, MQ2, Ultrasonic)

---

## 1. Power Supply Setup (LM2596 Buck Converter)

| Connection | Details |
|---|---|
| Battery (+) | → IN+ on LM2596 |
| Battery (–) | → IN– on LM2596 |

**Setting output voltage:**
- Power the LM2596 and measure voltage across OUT+ and OUT–
- Turn the blue potentiometer screw slowly until output reads exactly **5.0V**

---

## 2. Distribute 5V Output (LM2596 → Components)

Connect **LM2596 OUT+** to VCC of:
- Relay Module
- MQ2 Gas Sensor
- Ultrasonic Sensor (HC-SR04)

Connect **LM2596 OUT– (GND)** to GND of each component above **and** to ESP32 GND (shared ground).

> ⚠️ Always maintain a common ground between ESP32 and LM2596.

---

## 3. ESP32 GPIO Pin Connections

| GPIO Pin | Connected To |
|---|---|
| GPIO 4 | Relay IN1 (Light) |
| GPIO 5 | Relay IN2 (Fan) |
| GPIO 33 | DHT11 Data pin |
| GPIO 26 | LDR Module A0 |
| GPIO 27 | MQ2 A0 |
| GPIO 15 | Ultrasonic TRIG |
| GPIO 2 | Ultrasonic ECHO |
| GPIO 22 | OLED SDA |
| GPIO 23 | OLED SCL |
| GPIO 12 | Smoke Buzzer |
| GPIO 19 | Smoke LED (with 220Ω resistor) |
| GPIO 18 | Ultrasonic LED (with 220Ω resistor) |
| GPIO 16 (RX2) | HC-05 TX |
| GPIO 17 (TX2) | HC-05 RX (via voltage divider) |

---

## 4. 3.3V Components (Powered from ESP32 3.3V Pin)

### OLED Display (SSD1306)
| OLED Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 22 |
| SCL | GPIO 23 |

### DHT11 Sensor
| DHT11 Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 33 |

### LDR Module
| LDR Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| A0 | GPIO 26 |

### HC-05 Bluetooth Module
| HC-05 Pin | ESP32 Pin | Notes |
|---|---|---|
| VCC | 3.3V | |
| GND | GND | |
| TX | GPIO 16 (RX2) | Direct connection |
| RX | GPIO 17 (TX2) | **Via voltage divider** |

**HC-05 RX Voltage Divider** (3.3V logic → 3.3V safe for HC-05):
```
ESP32 GPIO 17 ──[1kΩ]──┬── HC-05 RX
                        │
                      [10kΩ]
                        │
                       GND
```

---

## 5. Safety Tips

- ✅ Always use a **shared ground** — connect ESP32 GND with LM2596 GND
- ❌ Never connect 5V directly to ESP32 3.3V pin
- ✅ Use **220Ω resistors** for all LEDs to prevent damage
- ✅ Verify LM2596 output voltage with a multimeter **before** connecting modules
- ✅ Secure connections with jumper wires or screw terminals
