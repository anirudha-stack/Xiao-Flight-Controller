// imu.h
#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include "LSM6DS3.h"
#include "Wire.h"

//Create a instance of class LSM6DS3

extern LSM6DS3 flightIMU;  // Declare flightIMU as an external variable

// Simple Kalman filter structure for 1D angle estimation
typedef struct {
  float angle;    // Current angle estimate
  float bias;     // Current gyro bias estimate
  float P[2][2];  // Error covariance matrix
  float Q_angle;  // Process noise variance for the angle
  float Q_bias;   // Process noise variance for the gyro bias
  float R_measure;// Measurement noise variance
} KalmanFilter;

// Declare KalmanFilter objects for roll & pitch

extern KalmanFilter kfRoll;
extern KalmanFilter kfPitch;


bool initialiseIMU();
void printImuValues();

// Initializes a Kalman filter struct
void initKalmanFilter(KalmanFilter &kf, float Q_angle, float Q_bias, float R_measure);

// Runs the Kalman prediction + update steps and returns the new angle
// newAngle: angle measured from accelerometer (degrees)
// newRate:  angular velocity from gyroscope (degrees/sec)
// dt:       time delta (seconds)
float kalmanGetAngle(KalmanFilter &kf, float newAngle, float newRate, float dt);

// Updates roll, pitch angles using the Kalman filter
void updateIMUAnglesWithKalman(float dt);

// Retrieve final roll, pitch, yaw angles (in degrees)
void getAngles(float &roll, float &pitch, float &yaw);

#endif  // IMU.H