#include "ambient.h"
#include "magnetic.h"

class RunStuff{
  private:
    GetColors getC;
    GetMagnetic getM;
  public:
  RunStuff(){
  };
  void runStart(){
    getC.getRGBC();
    getM.getField();
    Serial.print("r = ");
    Serial.println(getC.r);
    Serial.print("g = ");
    Serial.println(getC.g);
    Serial.print("b = ");
    Serial.println(getC.b);
    Serial.print("a = ");
    Serial.println(getC.a);
    Serial.print("magnetic heading = ");
    Serial.print(getM.heading);
    Serial.println();
    delay(1000);
  }
};

RunStuff runS;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  runS.runStart();
}