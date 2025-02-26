#include "pinConfig.h"
#include "utility.h"


void setup() {
  // put your setup code here, to run once:

  initialisePins();


}

void loop() {
  // put your main code here, to run repeatedly:

  testBatteryADC();

  delay(2000);
}
