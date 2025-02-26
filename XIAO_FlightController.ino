#include "pinConfig.h"
#include "utility.h"


void setup() {
  // put your setup code here, to run once:

  initialisePins();


}

void loop() {
  // put your main code here, to run repeatedly:

  testMotors();

  delay(2000);

  testIMU();

  delay(2000);

  testBatteryADC();

  delay(2000);
}
