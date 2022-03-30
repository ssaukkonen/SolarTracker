#include "ldr.h"

LDR::Ldr(){
	 
}
void LDR::beginLDR(){
	pinMode(ldrPinLeft, INPUT);
	pinMode(ldrPinRight, INPUT);
}
LDR::readLDR(){
	int leftLDRStatus = analogRead(ldrPinLeft);
	int rightLDRStatus = analogRead(ldrPinRight);
	return int leftLDRStatus, rightLDRStatus;
}	
LDR::diffLDR(int leftLDRStatus,int rightLDRStatus){
	leftLDR = leftLDRStatus; //???? miten tehdään oikein ja onko nämä mahdollisesti turhia
	rightLDR = rightLDRStatus;
	diff = leftLDR-rightLDR;
	return diff;
}	
LDR::giveDirection(int diff){	
	int diff = diff;				//tämä kans oikein
	char direction = "";		//onko liian pythonia
	if diff > jokuarvo{			//pitää vielä järkeillä kaikki vaihtoehdot
		direction = "right";
		return direction;
	}
	else if diff < jokuarvo2{
		direction = "left";
		return direction;
	}	
	else {
		direction = "no need";
		return direction;
	}
}
