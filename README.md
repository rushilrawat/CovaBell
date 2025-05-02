# 🚪 CovaBell - Smart Contactless Doorbell and Health Screening System

[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Language: C++](https://img.shields.io/badge/Made%20with-C++-brightgreen)](https://www.arduino.cc/reference/en/)

**CovaBell** is a smart contactless doorbell system that screens a visitor’s health vitals — temperature, oxygen level (SpO₂), and pulse rate — before unlocking a door using dual servos.  
Developed during the COVID-19 pandemic, it ensures safer access to homes, offices, and shops by automating standard screening checks.

---

## 📋 Features

- 🥵 **Fever Detection** via infrared temperature sensor
- 💓 **Pulse Rate Monitoring** using analog pulse sensor
- 🫁 **SpO₂ (Oxygen Level) Estimation** from analog input
- 🫀 **Heartbeat Presence Detection** via digital sensor
- 📺 **16x2 LCD Display** for live status and vitals
- 🚪 **Automatic Door Unlocking** using two servos
- 🔁 **Retry Mechanism** with max 3 attempts
- ⏳ **Inactivity Timeout** to reset the system
- 🔊 **Buzzer Alert** on access grant
- 🧱 Modular and readable code structure

---

## 🛠️ Hardware Used

| Component               | Pin Used      | Description                             |
|------------------------|---------------|-----------------------------------------|
| Arduino Uno/Nano       | —             | Microcontroller                         |
| IR Temp Sensor (Analog)| A1            | Non-contact temperature reading         |
| Pulse Sensor           | A2            | Analog pulse input                      |
| SpO₂ Sensor (Simulated)| A3            | Simulated analog input (85–100%)        |
| Heartbeat Sensor       | D10           | Digital input, HIGH = beat              |
| HC-SR04 (Ultrasonic)   | Trig: D7, Echo: D6 | Proximity trigger for scan         |
| Servo Motors (x2)      | D8, D9        | Unlock door                             |
| LCD 16x2 (No I2C)      | D12, D11, D5, D4, D3, D2 | Visitor interface               |
| Buzzer                 | D13           | Audio feedback                          |

> 💡 *MAX30100/SpO₂ modules can be integrated for real readings.*

---

## 🧰 Wiring Summary

- Connect temperature sensor to A1
- Pulse sensor to A2
- SpO₂ analog pin to A3
- Heartbeat module signal to pin 10
- HC-SR04: Trig → 7, Echo → 6
- Servo 1 → 8, Servo 2 → 9
- Buzzer → 13
- LCD → 12, 11, 5, 4, 3, 2 (non-I2C version)

---

## 🚀 Setup Instructions

1. **Connect All Components**  
   Wire the components as described above. Ensure your sensors have common GND and 5V from the Arduino.

2. **Upload the Code**  
   Open `CovaBell.ino` in the Arduino IDE.  
   Select your board (e.g., Arduino Uno), and upload the sketch.

3. **Power On**  
   Provide 5V power via USB or external adapter. The LCD should display:  
   `"System Ready"` → `"Awaiting Visitor"`

4. **How It Works**  
   - Visitor approaches ➔ Detected by ultrasonic sensor  
   - Temp, pulse, and SpO₂ are scanned  
   - If within limits ➔ Access granted (servos unlock, buzzer sounds)  
   - Else ➔ Retry allowed (up to 3 times)

---

## 📈 COVID-Style Screening Logic

| Parameter    | Safe Range     | Result if Abnormal       |
|--------------|----------------|---------------------------|
| Temperature  | ≤ 38°C         | Access denied             |
| Pulse Rate   | 50–120 BPM     | Access denied             |
| Oxygen Level | ≥ 94% SpO₂     | Access denied             |

> All 3 conditions must pass to unlock the door.

---

## 🔮 Future Enhancements

- 🌐 Wi-Fi alerts using ESP8266
- 🧠 Facial mask detection via camera modules
- 📊 Visitor logs with timestamps (EEPROM or SD)

---

## 👥 Contributors

- [Rushil Rawat](https://github.com/RushilRawat)  
- [Arnav Bansal](https://github.com/ArnavBansal11)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
