#include <assert.h>
#include "wirish.h"
#include "Motor.h"

Motor Motor::motor;
const unsigned char Motor::pin[4] = {D28,D27,D11,D12};
unsigned short Motor::data[4];

Motor::Motor()
{
	/* pin mode setup related to motor should has to be put here*/
	pinMode(D28,PWM);
	pinMode(D27,PWM);
	pinMode(D11,PWM);
	pinMode(D12,PWM);
	Timer3.setPeriod(2080);
	
	for(int index = 0 ; index < 4 ; index++)
		control(index,0);
}

Motor::~Motor()
{
}

void Motor::control(int index,unsigned short level)
{
#ifndef NDEBUG
	assert(0 <= index && index <= 3);
	assert(0 <= level && level <= 1000);
#endif
	pwmWrite(pin[index],levelToCtrl(level));
}

void Motor::control1(unsigned short level)
{
	motor.control(0,level);
	data[0] = level;
}

void Motor::control2(unsigned short level)
{
	motor.control(1,level);
	data[1] = level;
}

void Motor::control3(unsigned short level)
{
	motor.control(2,level);
	data[2] = level;
}

void Motor::control4(unsigned short level)
{
	motor.control(3,level);
	data[3] = level;
}

unsigned short Motor::getLevel1()
{
	return data[0];
}

unsigned short Motor::getLevel2()
{
	return data[1];
}

unsigned short Motor::getLevel3()
{
	return data[2];
}

unsigned short Motor::getLevel4()
{
	return data[2];
}

unsigned short Motor::levelToCtrl(unsigned short level)
{
	unsigned short ctrl = (level <= 0)?0:((level >= 1000)?50000:((1000 + level) * 24));
	return ctrl;
}
