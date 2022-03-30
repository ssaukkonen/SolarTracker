#ifndef LDR_H
#define LDR_H
#include <Arduino.h>


class LDR {
	public:
		Ldr();
		void beginLDR();
	private:
		int i;
		int ldrPinLeft = A0; //nämä oikein
		int ldrPinRight = A1;
		readLDR();
		diffLDR();
		giveDirection();
};
#endif
