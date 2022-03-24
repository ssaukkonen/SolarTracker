#ifndef AMBIENT_H
#define AMBIENT_H
#include <Arduino.h>
#include <Arduino_APDS9960.h>

class GetColors {
  public:
    GetColors();
    void getRGBC();
    int r, g, b, a;
};
#endif
