#include "pinConfig.h"

void initialisePins() {
    // Motor pins as OUTPUT
    pinMode(MOTOR_FRONT_LEFT, OUTPUT);
    pinMode(MOTOR_FRONT_RIGHT, OUTPUT);
    pinMode(MOTOR_BACK_LEFT, OUTPUT);
    pinMode(MOTOR_BACK_RIGHT, OUTPUT);

    // Ensure motors are off initially
    digitalWrite(MOTOR_FRONT_LEFT, LOW);
    digitalWrite(MOTOR_FRONT_RIGHT, LOW);
    digitalWrite(MOTOR_BACK_LEFT, LOW);
    digitalWrite(MOTOR_BACK_RIGHT, LOW);

    // Battery ADC as INPUT
    pinMode(BATTERY_ADC, INPUT);

    // Initialize I2C (IMU)
    Wire.begin(IMU_SDA, IMU_SCL, 400000);  // 400kHz I2C

    // Start Serial Logging if enabled
    if (LOG_ENABLED) {
        Serial.begin(SERIAL_BAUD_RATE);
        Serial.println("Hello, XIAO Flight Controller is now starting ...\n");
    }
}
