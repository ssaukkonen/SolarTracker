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
		delay(50);
	}
	while (curPos>position1){
		curPos--;
		servo1.write(curPos);
		delay(50);
	}
}
		
void Servomoottori::moveServo(String direction){
  int newPos = 0;
  if (direction == "right"){
		newPos = curPos - 10;
    if (newPos < 15){
      newPos = 15;
    }
	}
	else if (direction == "left"){
		newPos = curPos + 10;
    if (newPos > 165){
      newPos = 165;
    }
  }
  setServo(newPos);
}