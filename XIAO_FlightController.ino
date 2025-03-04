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


  

}



void loop() {
    static unsigned long lastTime = 0;
    unsigned long currentTime = millis();
    float dt = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
    lastTime = currentTime;

    // Ensure dt is non-zero to avoid division errors
    if (dt <= 0) return;

    // Update IMU angles using Complementary Filter
    updateIMUAngles(dt);

    // Retrieve filtered roll, pitch, yaw values
    float roll, pitch, yaw;
    getAngles(roll, pitch, yaw);

    // Send formatted data to Processing (or any external visualization)
    Serial.print(roll, 2);
    Serial.print(",");
    Serial.print(pitch, 2);
    Serial.print(",");
    Serial.println(yaw, 2);

    delay(5); // Reduce latency for smoother rendering
}
