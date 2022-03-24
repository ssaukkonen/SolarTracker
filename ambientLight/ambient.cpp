#include "ambient.h"

GetColors::GetColors(){
}

void GetColors::getRGBC(){
  APDS.begin();
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  APDS.readColor(r, g, b, a);
  APDS.end();
}
