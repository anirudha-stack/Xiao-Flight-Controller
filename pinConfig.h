#ifndef PINCONFIG_H
#define PINCONFIG_H

#include <Arduino.h>
#include <Wire.h>

// Enable logging
#define LOG_ENABLED true

// Motor Pin Definitions
#define MOTOR_FRONT_LEFT  D9
#define MOTOR_FRONT_RIGHT D10
#define MOTOR_BACK_LEFT   D8
#define MOTOR_BACK_RIGHT  D7

// IMU (I2C) Pins
#define IMU_SDA D4
#define IMU_SCL D5

// Battery ADC Pin
#define BATTERY_ADC A0

// Serial Baud Rate
#define SERIAL_BAUD_RATE 115200

// Function Prototype
void initialisePins();

#endif // PINCONFIG_H
