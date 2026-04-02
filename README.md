# Esp32-mini-drone

# 🛰️ ESP32-nRF24-Drone-Link
**A high-reliability, 4-channel DIY RC System for Drones & Robotics.**

This project utilizes the **ESP32 DevKit V1** and **nRF24L01+PA+LNA** to create a long-range transmitter and receiver system. It features real-time telemetry on a 1.8" TFT display and a robust software failsafe for drone safety.

---

## 🚀 Key Features
- **Range:** 1km+ (Optimized via 250kbps & PA+LNA).
- **Interference Rejection:** Uses Channel 110 (2.510 GHz) to stay clear of WiFi.
- **Failsafe:** Automatic throttle cut and stick centering if signal is lost for >500ms.
- **Visuals:** Real-time channel data display on a 1.8" ST7735 TFT.
- **Connection Status:** Onboard Blue LED indicates active ACK (Acknowledgement) from the receiver.

---
## ⚙️ Custom Coreless Motor Driver
This project includes a **Custom-Built Micro Motor Driver** specifically designed for high-RPM coreless motors.
- **Drive Type:** MOSFET-based PWM control.
- **Compatibility:** Optimized for 3.7V - 4.2V (1S) coreless motors.
- **Integrated Failsafe:** Motor power is automatically cut by the ESP32 if the nRF24L01 signal is lost for more than 500ms.
---

## 🔌 Hardware Pin Mapping

### 1. Transmitter (TX) Connections

| Component       | Pin Label | ESP32 Pin    |    Function         |
| :---            | :---      | :---         | :---                |
| **nRF24L01**    | VCC       | **Vin (5V)** | Power via Adapter   |
| **nRF24L01**    | GND       | **GND**      | Common Ground       |
| **nRF24L01**    | CE        | **GPIO 4**   | Radio Enable        |
| **nRF24L01**    | CSN       | **GPIO 5**   | SPI Chip Select     |
| **nRF24L01**    | SCK       | **GPIO 18**  | SPI Clock (VSPI)    |
| **nRF24L01**    | MOSI      | **GPIO 23**  | SPI Data Out (VSPI) |
| **nRF24L01**    | MISO      | **GPIO 19**  | SPI Data In (VSPI)  |
| **Left Stick**  | VRX       | **GPIO 34**  | Throttle (Analog)   |
| **Left Stick**  | VRY       | **GPIO 35**  | Yaw (Analog)        |
| **Right Stick** | VRX       | **GPIO 32**  | Pitch (Analog)      |
| **Right Stick** | VRY       | **GPIO 33**  | Roll (Analog)       |
| **Status**      | LED       | **GPIO 2**   | Connection LED      |

### 2. Receiver (RX) Connections

| Component    | Pin Label | ESP32 Pin      | Function       |
| :---         | :---      | :---           | :---           |
| **nRF24L01** | CE / CSN  | **GPIO 4 / 5** | Same as TX     |
| **nRF24L01** | SPI Pins  | **18, 19, 23** | Same as TX     |
| **1.8" TFT** | SCL (SCK) | **GPIO 14**    | HSPI Clock     |
| **1.8" TFT** | SDA (MOSI)| **GPIO 13**    | HSPI Data      |
| **1.8" TFT** | CS        | **GPIO 15**    | Display Select |
| **1.8" TFT** | DC (A0)   | **GPIO 21**    | Data/Command   |
| **1.8" TFT** | RES (RST) | **GPIO 22**    | Screen Reset   |
| **1.8" TFT** | LED (BL)  | **3V3**        | Backlight      |

---

## ⚠️ Critical Stability Components

| Component       | Value    | Placement     | Purpose                       |
| :---            | :---     | :---          | :---                          |
| **Capacitor 1** | 100uF    | nRF VCC / GND | Prevents TX flickering        |
| **Regulator**   | AMS1117  | nRF Adapter   | Safe 5V to 3.3V step-down     |
| **Antenna**     | SMA 2.4G | nRF Module    | Required for PA+LNA operation |

---

## 🛠️ Software Setup
1. **Libraries:** Install `RF24` by TMRh20, `Adafruit GFX`, and `Adafruit ST7735` via the Arduino Library Manager.
2. **Channel:** Ensure both TX and RX are set to `radio.setChannel(110)`.
3. **Data Rate:** Set to `radio.setDataRate(RF24_250KBPS)` for maximum range.
4. **Board:** Select **DOIT ESP32 DEVKIT V1** in the Arduino IDE.

---

## 📝 License
This project is open-source. Feel free to use and modify for your own RC builds.
