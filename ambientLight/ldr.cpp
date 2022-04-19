#include "ldr.h"

LDR::Ldr(){
	 
}
void LDR::beginLDR(){
	pinMode(ldrPinLeft, INPUT);
	pinMode(ldrPinRight, INPUT);
}
void LDR::readLDR(){
	int leftLDRStatus = analogRead(ldrPinLeft);
	int rightLDRStatus = analogRead(ldrPinRight);
	diffLDR();
	//return int leftLDRStatus, rightLDRStatus;
}	
void LDR::diffLDR(int rightLDRStatus int leftLDRStatus){
	leftLDR = leftLDRStatus; //???? miten tehdään oikein ja onko nämä mahdollisesti turhia
	rightLDR = rightLDRStatus;
	diff = leftLDR-rightLDR;
	giveDirection();
	//return diff;
}	
LDR::giveDirection(int diff){	
	int diff = diff;				//tämä kans oikein
	char direction = "";		//onko liian pythonia
	if diff > jokuarvo{			//pitää vielä järkeillä kaikki vaihtoehdot ja keksiä arvot
		direction = "right";
		return direction;
	}
	else if diff < jokuarvo2{
		direction = "left";
		return direction;
	}	
	else {
		direction = "stop";
		return direction;
	}
}
