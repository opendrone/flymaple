#ifndef MOTOR_H
#define MOTOR_H

#include "Vector.h"

class Motor {
	static Motor motor;
	static const unsigned char pin[4];
	static unsigned short data[4];
  
	Motor();
	void control(int index,unsigned short level);
	unsigned short levelToCtrl(unsigned short level);
public:
	~Motor();
	static void control1(unsigned short level);
	static void control2(unsigned short level);
	static void control3(unsigned short level);
	static void control4(unsigned short level);
	static unsigned short getLevel1();
	static unsigned short getLevel2();
	static unsigned short getLevel3();
	static unsigned short getLevel4();
};

#endif
