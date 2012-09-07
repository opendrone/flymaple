#ifndef MOTOR_H
#define MOTOR_H

#include "Vector.h"

class Motor {
	static Motor motors[4];
	static bool isTimerInit;
	
	unsigned char pin;
	unsigned short data;
  
	Motor(unsigned char pin);
	Motor(const Motor & motor);
	void control(unsigned short level);
	unsigned short levelToCtrl(unsigned short level);
public:
	~Motor();
	static void control1(unsigned short level);
	static void control2(unsigned short level);
	static void control3(unsigned short level);
	static void control4(unsigned short level);
	static Vector<double> getSpeed();
};

#endif
