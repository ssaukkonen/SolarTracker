#include "ldr.h"

LDR::LDR(){
	 
}
void LDR::beginLDR(){
	pinMode(ldrPinLeft, INPUT);
	pinMode(ldrPinRight, INPUT);
}
void LDR::readLDR(){
	int leftLDRStatus = analogRead(ldrPinLeft);
	int rightLDRStatus = analogRead(ldrPinRight);
	diffLDR(rightLDRStatus, leftLDRStatus);
}	
void LDR::diffLDR(int rightLDRStatus, int leftLDRStatus){
	diff = rightLDRStatus-leftLDRStatus;
	Serial.println(diff);
  giveDirection(diff);
}	
void LDR::giveDirection(int diff){	
	if (diff > 10){
		direction = "left";
	}
	else if (diff < -10){
		direction = "right";
	}	
	else {
		direction = "center";
	}
}