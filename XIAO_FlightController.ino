#include "pinConfig.h"
#include "utility.h"
#include "imu.h"

void setup() {
  // put your setup code here, to run once:

  initialisePins();
  bool imuUp = initialiseIMU();

  while(!imuUp){
   Serial.println("IMU not booted, retrying in 3s...");
   delay(3000);
   imuUp = initialiseIMU();
  }


  // Initialize each Kalman filter with typical noise values.
  // Tweak them to tune performance:
  // Q_angle   ~ process noise in angle
  // Q_bias    ~ process noise in gyro bias
  // R_measure ~ measurement noise from accelerometer
  initKalmanFilter(kfRoll,  0.001f, 0.003f, 0.03f);
  initKalmanFilter(kfPitch, 0.001f, 0.003f, 0.03f);

  // Optionally, read initial accel data and set initial angles accordingly
  // ...


}

unsigned long prevTime = 0;

void loop() {

  unsigned long currTime = millis();
  float dt = (currTime - prevTime) / 1000.0f; // ms to seconds
  prevTime = currTime;

  // Update angles with the Kalman filter
  updateIMUAnglesWithKalman(dt);

  // Retrieve final angles
  float roll, pitch, yaw;
  getAngles(roll, pitch, yaw);

  // Print for debugging
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print("  Pitch: ");
  Serial.print(pitch);
  Serial.print("  Yaw: ");
  Serial.println(yaw);

  delay(10);  // Adjust loop rate as needed
}
