#ifndef LDR_H
#define LDR_H
#include <Arduino.h>


class LDR {
	public:
		Ldr();
		void beginLDR();
	private:
		int i;
		int ldrPinLeft = A3; //nämä oikein
		int ldrPinRight = A2;
		void readLDR();
		void diffLDR();
		giveDirection(); // public?
		int leftLDRStatus;
		int rightLDRStatus
		int leftLDR;
		int rightLDR;
		int diff;
		char direction;
};
#endif
