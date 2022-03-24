#include "magnetic.h"

GetMagnetic::GetMagnetic(){
}

void GetMagnetic::getField(){
  IMU.begin();
  while (! IMU.magneticFieldAvailable()) {
    delay(5);
  }
  IMU.readMagneticField(x, y, z);
  IMU.end();
  float Pi = 3.14159;
  heading = (atan2(y, x) * 180) / Pi;
  if (heading < 0)
  {
    heading = 360 + heading;
  }
}
