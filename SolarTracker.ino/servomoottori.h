#ifndef SERVOMOOTTORI_H
#define SERVOMOOTTORI_H
#include <Arduino.h>
#include <Servo.h>

class Servomoottori {
	public:
		Servomoottori();
		void beginServo();
		void setServo(int);
		void manualServo(int);
    void moveServo(String);
		int curPos;		
	private:
		Servo servo1;
		int angleDiff;
		int desiredAngle;
    int position1;
};
#endif