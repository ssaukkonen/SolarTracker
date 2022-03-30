#include "servomoottori.h"

Servomoottori::Servomoottori(){
	  
}
void Servomoottori::beginServo(){
	curPos=95;
	servo1.attach(2);
	servo1.write(curPos);
  
}
void Servomoottori::setServo(int position1){
	
	
	while (curPos<position1){
		curPos++;
		servo1.write(curPos);
		delay(15);
	}
	while (curPos>position1){
		curPos--;
		servo1.write(curPos);
		delay(15);
	}
	curPos = position1;
	}
	
void Servomoottori::moveServo(char direction){
	switch(direction) {
  case "left":
    for (int i = 0; i <= 10; i = i++) {
		curPos(i);
		servo1.write(curPos);
		delay(15);
	}
    break;
  case "right":
    for (int i = 0; i <= -10; i = i--) {
		curPos(i);
		servo1.write(curPos);
		delay(15);
	}
	break;
  case "no need":
    break;

}
	
}
void Servomoottori::moveServo(char direction){
	if direction == "left"{
		for (int i = 0; i <= 10; i = i++) {
		curPos(i);
		servo1.write(curPos);
		delay(15);
		}
	}
	else if direction == "right"{
		for (int i = 0; i <= 10; i = i++) {
		curPos(i);
		servo1.write(curPos);
		delay(15);
		}
	else {
		break;
	}		
	}
}	