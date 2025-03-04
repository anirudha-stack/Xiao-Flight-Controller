#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "LSM6DS3.h"
#include "Wire.h"

// Create an instance of the LSM6DS3 IMU
extern LSM6DS3 flightIMU;

// Function declarations
bool initialiseIMU();
void printImuValues();

// Complementary Filter Functions
void updateIMUAngles(float dt);
void getAngles(float &roll, float &pitch, float &yaw);
void resetYaw();

#endif // IMU_H
