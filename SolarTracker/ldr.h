#ifndef LDR_H
#define LDR_H
#include <Arduino.h>

class LDR {
	public:
		LDR();
		void beginLDR();
    void readLDR();
    String direction = "center";
	private:
		int ldrPinLeft = A3;
		int ldrPinRight = A2;
		void diffLDR(int, int);
		void giveDirection(int);
		int diff;
};
#endif