# XIAO Flight Controller

## Overview

The **XIAO Flight Controller** is a lightweight and compact flight controller designed around the **Seeed Studio XIAO ESP32C3** microcontroller. It integrates an **LSM6DS3 IMU** for motion sensing and features motor drivers to control quadcopter motors. The board is powered by a **VBAT supply** and includes essential power management components.

## Features

- **Microcontroller:** Seeed Studio XIAO ESP32C3
- **IMU Sensor:** LSM6DS3 (6-axis accelerometer and gyroscope)
- **Motor Drivers:** SI2302 MOSFETs for motor control
- **Battery Monitoring:** ADC-based battery voltage sensing
- **Communication Interfaces:**
  - **I2C:** IMU communication (SCL/SDA)
  - **SPI:** Available for expansion
  - **UART:** Debugging and communication
- **Power Management:**
  - RT9193-33GB voltage regulator for stable 3.3V output
  - Large capacitor for noise filtering
- **Other Components:**
  - Pull-up and pull-down resistors for signal stability
  - Protection diodes for power safety

## Hardware Components

| Component     | Description                        |
|--------------|------------------------------------|
| **MCU**      | Seeed Studio XIAO ESP32C3         |
| **IMU**      | LSM6DS3TR (6-axis IMU)            |
| **Motor MOSFETs** | SI2302                        |
| **Power Regulator** | RT9193-33GB (3.3V LDO)      |
| **Battery Monitor** | Voltage divider (200KΩ resistors) |
| **Capacitors** | 10uF and 1000uF for power stability |
| **Diodes**   | 1N4148 for circuit protection     |

## Pin Configuration

| XIAO ESP32C3 Pin | Function       |
|------------------|---------------|
| P6 (D4)         | SDA (I2C)      |
| P7 (D5)         | SCL (I2C)      |
| P10 (D3)        | SPI MOSI       |
| P9 (D2)         | SPI MISO       |
| P8 (D1)         | SPI SCK        |
| P0 (D6)         | UART TX        |
| P1 (D7)         | UART RX        |
| P26 (A0)        | ADC (Battery)  |

## Schematic

The schematic for this project can be found in **XIAO_FlightController.SchDoc**.

## Setup & Usage

### 1. Prerequisites

- **Arduino IDE** with ESP32 board support installed
- **Seeed Studio XIAO ESP32C3** drivers
- **I2Cdev library** for IMU communication
- **Flight control firmware** (to be developed)

### 2. Flashing the Firmware

1. Connect the **XIAO ESP32C3** via USB.
2. Open the Arduino IDE and select the correct board (**ESP32C3 XIAO**).
3. Load the flight controller firmware.
4. Compile and upload the code.

### 3. Connecting the Hardware

- **Power Supply:** Connect VBAT (3S/4S LiPo) to power the board.
- **Motors:** Connect quadcopter motors to the respective motor pads.
- **IMU:** Ensure I2C lines (SDA/SCL) are properly connected.
- **Battery Voltage Sensing:** Ensure the ADC_BATTERY line is properly connected.

### 4. Testing & Calibration

- Use **serial debugging** to check IMU readings.
- Test motor control using PWM signals.
- Calibrate the IMU for accurate flight control.

## Future Improvements

- Implement **PID control** for stable flight.
- Integrate **GPS module** for navigation.
- Support **wireless telemetry** using ESP32C3’s Wi-Fi.
- Develop an **Android app** for real-time flight monitoring.

## License

This project is open-source under the **MIT License**.

---

📌 *For detailed schematics and development updates, refer to the documentation folder in this repository.*
