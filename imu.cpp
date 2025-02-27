#include "imu.h"

// Create a single instance of the LSM6DS3
LSM6DS3 flightIMU(I2C_MODE, 0x6A);

// We'll track Roll, Pitch, Yaw in degrees
static float g_roll  = 0.0f;
static float g_pitch = 0.0f;
static float g_yaw   = 0.0f;  // drift-only for demonstration, no magnetometer-based correction

// Define our two Kalman filters (one for roll, one for pitch)
 KalmanFilter kfRoll;
 KalmanFilter kfPitch;

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
// KALMAN FILTER CORE
//----------------------------------------------------

// Initializes the Kalman filter structure
void initKalmanFilter(KalmanFilter &kf, float Q_angle, float Q_bias, float R_measure) {
  kf.angle = 0.0f;
  kf.bias = 0.0f;
  
  // Error covariance matrix
  kf.P[0][0] = 0.0f;
  kf.P[0][1] = 0.0f;
  kf.P[1][0] = 0.0f;
  kf.P[1][1] = 0.0f;

  // Tunable parameters
  kf.Q_angle   = Q_angle;
  kf.Q_bias    = Q_bias;
  kf.R_measure = R_measure;
}

// Performs a single Kalman filter predict/update cycle
float kalmanGetAngle(KalmanFilter &kf, float newAngle, float newRate, float dt) {
  // 1. PREDICTION STEP
  // Update the angle using the gyroscope rate minus our current bias
  float rate = newRate - kf.bias;
  kf.angle += dt * rate;

  // Update the error covariance matrix
  // P = P + Q
  kf.P[0][0] += dt * (dt*kf.P[1][1] - kf.P[0][1] - kf.P[1][0] + kf.Q_angle);
  kf.P[0][1] -= dt * kf.P[1][1];
  kf.P[1][0] -= dt * kf.P[1][1];
  kf.P[1][1] += kf.Q_bias * dt;

  // 2. UPDATE STEP
  // Our measurement is newAngle from the accelerometer
  float S = kf.P[0][0] + kf.R_measure; // Estimate error
  float K0 = kf.P[0][0] / S;          // Kalman gain for angle
  float K1 = kf.P[1][0] / S;          // Kalman gain for bias

  // Y (innovation) = z - H*x  (where z is newAngle, H*x is predicted angle)
  float y = newAngle - kf.angle;

  // Update angle, bias with innovation
  kf.angle += K0 * y;
  kf.bias  += K1 * y;

  // Update error covariance matrix
  float P00_temp = kf.P[0][0];
  float P01_temp = kf.P[0][1];

  kf.P[0][0] -= K0 * P00_temp;
  kf.P[0][1] -= K0 * P01_temp;
  kf.P[1][0] -= K1 * P00_temp;
  kf.P[1][1] -= K1 * P01_temp;

  return kf.angle;
}

//----------------------------------------------------
// UPDATE ORIENTATION (ROLL, PITCH, YAW)
//----------------------------------------------------
void updateIMUAnglesWithKalman(float dt) {
  // 1. Read raw data
  float gx = flightIMU.readFloatGyroX();   // deg/sec
  float gy = flightIMU.readFloatGyroY();   // deg/sec
  float gz = flightIMU.readFloatGyroZ();   // deg/sec
  float ax = flightIMU.readFloatAccelX();  // g
  float ay = flightIMU.readFloatAccelY();  // g
  float az = flightIMU.readFloatAccelZ();  // g

  // 2. Compute angles from accelerometer (roll, pitch)
  // Adjust signs/orientations if your sensor axis differs
  float accRoll  = atan2(ay, az) * 180.0f / PI;
  float accPitch = atan2(-ax, sqrt(ay*ay + az*az)) * 180.0f / PI;
  
  // 3. Predict + update step for ROLL
  g_roll = kalmanGetAngle(kfRoll, accRoll, gx, dt);

  // 4. Predict + update step for PITCH
  g_pitch = kalmanGetAngle(kfPitch, accPitch, gy, dt);

  // 5. For YAW we have no absolute reference, so we just integrate
  //    This will drift over time without a magnetometer
  g_yaw += gz * dt; // rudimentary approach
}

//----------------------------------------------------
// GET THE FILTERED ANGLES
//----------------------------------------------------
void getAngles(float &roll, float &pitch, float &yaw) {
  roll  = g_roll;
  pitch = g_pitch;
  yaw   = g_yaw;
}
