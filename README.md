# CovaBell - Smart Contactless Doorbell and Lock System 🚪📈

CovaBell is an innovative project designed to provide a safer, contactless way of admitting visitors by screening their health vitals such as body temperature (and optionally oxygen level and pulse). Developed during the COVID-19 pandemic, it automates safety checks and physical access control using Arduino, sensors, and servo motors.

---

## 📋 Features
- Contactless temperature scanning using an infrared sensor.
- Automatic door unlocking with servo motors upon passing health check.
- Retry mechanism if abnormal temperature detected (max 3 retries).
- Timeout reset after visitor inactivity.
- Idle display when system is not in use.
- Buzz alert on access grant.
- Modular code design for easy expansion.

---

## 🛠️ Hardware Used
- Arduino UNO
- Ultrasonic Sensor (HC-SR04)
- IR Temperature Sensor (Analog)
- LCD Display 16x2 with I2C
- Servo Motors x 2
- Buzzer
- Optional Add-ons:
  - MAX30100 Pulse Oximeter Sensor
  - Heartbeat Sensor Module
  - Temperature Shield

---

## 🚀 Setup Instructions
1. Wire up all components according to the provided schematic.
2. Upload the `CovaBell.ino` code onto your Arduino.
3. Power the Arduino board (5V recommended).
4. Observe LCD messages and interact with the system.

---

## 📈 How it Works
- Visitor approaches ➔ Ultrasonic sensor detects.
- Visitor's forehead is scanned ➔ Temperature is measured.
- If within safe range:
  - Door unlocks for 5 seconds.
  - Welcome buzzer is activated.
- If temperature is high:
  - Retry opportunity provided up to 3 attempts.
  - Else access denied.

---

## 🔮 Future Enhancements
- Integrate cloud notification (via WiFi module ESP8266).
- Add facial mask detection using basic camera modules.
- Track visitor logs for auditing.

---

## 👥 Contributors
- [Rushil Rawat](https://github.com/RushilRawat)
- [Arnav Bansal](https://github.com/ArnavBansal11)

---

## 📜 License
This project is licensed under the MIT License - see the LICENSE file for details.
