#include "pinConfig.h"
#include "utility.h"
#include "imu.h"
#include "pid.h"

PIDController pitchPID;
unsigned long lastTime = 0;


void setup() {
  // put your setup code here, to run once:

  initialisePins();
  bool imuUp = initialiseIMU();

  while(!imuUp){
   Serial.println("IMU not booted, retrying in 3s...");
   delay(3000);
   imuUp = initialiseIMU();
  }


    float roll, pitch, yaw;
    getAngles(roll, pitch, yaw);

    // Initialize PID with the starting pitch
    initPID(pitchPID, 0, 0, 0.05, -100, 100, pitch);
  

}



void loop() {
    float roll, pitch, yaw;
    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0;
    lastTime = currentTime;

    // Get current pitch from IMU
    updateIMUAngles(dt);
    getAngles(roll, pitch, yaw);

    // Compute PID output and apply to motors
    float pidOutput = computePID(pitchPID, pitch, dt);
    Serial.println(pidOutput);
    applyMotorControl(pidOutput);

    delay(10);  // Small delay for control loop stability
}
