#ifndef SERVOMOOTTORI_H
#define SERVOMOOTTORI_H
#include <Arduino.h>
#include <Servo.h>

class Servomoottori {
	public:
		Servomoottori();
		void beginServo();
		void setServo(int);
		int position1;
	private:
		Servo servo1;
		int curPos;
};
#endif
