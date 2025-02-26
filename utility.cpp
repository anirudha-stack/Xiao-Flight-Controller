#include "utility.h"

// Test function for Motors with Serial Prints
void testMotors() {
    Serial.println("Starting Motor Test...");
    
    pinMode(MOTOR_FRONT_LEFT, OUTPUT);
    pinMode(MOTOR_FRONT_RIGHT, OUTPUT);
    pinMode(MOTOR_BACK_LEFT, OUTPUT);
    pinMode(MOTOR_BACK_RIGHT, OUTPUT);
    
    // Test Front Left Motor
    Serial.println("Testing Front Left Motor...");
    for (int pwm = 0; pwm <= 255; pwm += 5) {
        Serial.print("Front Left PWM: ");
        Serial.println(pwm);
        analogWrite(MOTOR_FRONT_LEFT, pwm);
        delay(50);
    }
    analogWrite(MOTOR_FRONT_LEFT, 0);
    Serial.println("Front Left Motor Test Complete.");
    delay(500);
    
    // Test Front Right Motor
    Serial.println("Testing Front Right Motor...");
    for (int pwm = 0; pwm <= 255; pwm += 5) {
        Serial.print("Front Right PWM: ");
        Serial.println(pwm);
        analogWrite(MOTOR_FRONT_RIGHT, pwm);
        delay(50);
    }
    analogWrite(MOTOR_FRONT_RIGHT, 0);
    Serial.println("Front Right Motor Test Complete.");
    delay(500);
    
    // Test Back Left Motor
    Serial.println("Testing Back Left Motor...");
    for (int pwm = 0; pwm <= 255; pwm += 5) {
        Serial.print("Back Left PWM: ");
        Serial.println(pwm);
        analogWrite(MOTOR_BACK_LEFT, pwm);
        delay(50);
    }
    analogWrite(MOTOR_BACK_LEFT, 0);
    Serial.println("Back Left Motor Test Complete.");
    delay(500);
    
    // Test Back Right Motor
    Serial.println("Testing Back Right Motor...");
    for (int pwm = 0; pwm <= 255; pwm += 5) {
        Serial.print("Back Right PWM: ");
        Serial.println(pwm);
        analogWrite(MOTOR_BACK_RIGHT, pwm);
        delay(50);
    }
    analogWrite(MOTOR_BACK_RIGHT, 0);
    Serial.println("Back Right Motor Test Complete.");
    delay(500);
    
    Serial.println("Motor Test Completed Successfully.");
}

// Test function for IMU
void testIMU() {
    Serial.println("Testing IMU...");
    Wire.begin();
    Wire.beginTransmission(0x6A); // LSM6DS3 I2C address
    if (Wire.endTransmission() == 0) {
        Serial.println("IMU detected successfully.");
    } else {
        Serial.println("IMU not found!");
    }
}

// Test function for Battery ADC
void testBatteryADC() {
    Serial.println("Testing Battery ADC...");
    pinMode(BATTERY_ADC, INPUT);
    int adcValue = analogRead(BATTERY_ADC);
    float calibrationFactor = 3.11 / 3.44; // Adjust based on real measurements
    float voltage = (adcValue / 4095.0) * 3.3 * ((200 + 200) / 200.0) * calibrationFactor;
    Serial.print("Battery Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
}
