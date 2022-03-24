#ifndef MAGNETIC_H
#define MAGNETIC_H
#include <Arduino.h>
#include <Arduino_LSM9DS1.h> >

class GetMagnetic {
  public:
    GetMagnetic();
    void getField();
    float heading;
  private:
    float x, y, z;
};
#endif
