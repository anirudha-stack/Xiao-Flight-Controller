#include "imu.h"
#include <math.h>

// Create a single instance of the LSM6DS3
LSM6DS3 flightIMU(I2C_MODE, 0x6A);

// Complementary Filter Variables
static float roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
static float gyroBiasX = 0.0f, gyroBiasY = 0.0f, gyroBiasZ = 0.0f;
static float alpha = 0.98f; // Adaptive filter coefficient

//----------------------------------------------------
// IMU INIT & PRINT
//----------------------------------------------------

bool initialiseIMU() {
  if (flightIMU.begin() != 0) {
    return false;
  } else {
    return true;
  }
}

void printImuValues() {
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X1 = ");
  Serial.println(flightIMU.readFloatAccelX(), 4);
  Serial.print(" Y1 = ");
  Serial.println(flightIMU.readFloatAccelY(), 4);
  Serial.print(" Z1 = ");
  Serial.println(flightIMU.readFloatAccelZ(), 4);

  Serial.print("\nGyroscope:\n");
  Serial.print(" X1 = ");
  Serial.println(flightIMU.readFloatGyroX(), 4);
  Serial.print(" Y1 = ");
  Serial.println(flightIMU.readFloatGyroY(), 4);
  Serial.print(" Z1 = ");
  Serial.println(flightIMU.readFloatGyroZ(), 4);

  Serial.print("\nThermometer:\n");
  Serial.print(" Degrees C1 = ");
  Serial.println(flightIMU.readTempC(), 4);
  Serial.print(" Degrees F1 = ");
  Serial.println(flightIMU.readTempF(), 4);
}

//----------------------------------------------------
// COMPLEMENTARY FILTER FUNCTIONS
//----------------------------------------------------
float computeAdaptiveAlpha(float ax, float ay, float az) {
    float accMagnitude = sqrt(ax * ax + ay * ay + az * az);
    return constrain(0.98f - (accMagnitude - 1.0f) * 0.02f, 0.90f, 0.98f);
}

void updateIMUAngles(float dt) {
    float gx = flightIMU.readFloatGyroX();
    float gy = flightIMU.readFloatGyroY();
    float gz = flightIMU.readFloatGyroZ();
    float ax = flightIMU.readFloatAccelX();
    float ay = flightIMU.readFloatAccelY();
    float az = flightIMU.readFloatAccelZ();

    //alpha = computeAdaptiveAlpha(ax, ay, az);
    alpha =0.98;


    float accRoll = atan2(ay, az) * 180.0f / M_PI;
    float accPitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / M_PI;

    roll = alpha * (roll + (gx - gyroBiasX) * dt) + (1 - alpha) * accRoll;
    pitch = alpha * (pitch + (gy - gyroBiasY) * dt) + (1 - alpha) * accPitch;
    yaw += (gz - gyroBiasZ) * dt;
}

void getAngles(float &r, float &p, float &y) {
    r = roll;
    p = pitch;
    y = yaw;
}

void resetYaw() {
    yaw = 0.0f;
}
