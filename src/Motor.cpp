#include <assert.h>
#include "wirish.h"
#include "Motor.h"

Motor Motor::motor1 __attribute__((init_priority(3000)))(D28);
Motor Motor::motor2 __attribute__((init_priority(3000)))(D27);
Motor Motor::motor3 __attribute__((init_priority(3000)))(D11);
Motor Motor::motor4 __attribute__((init_priority(3000)))(D12);

Motor::Motor(unsigned char p)
:pin(p),data(0)
{
}

Motor::Motor(const Motor & motor)
:pin(motor.pin),data(motor.data)
{
}

Motor::~Motor()
{
}

void Motor::control(unsigned short level)
{
#ifndef NDEBUG
	assert(0 <= level && level <= 1000);
#endif
	pwmWrite(pin,levelToCtrl(level));
}

void Motor::control1(unsigned short level)
{
	motor1.control(level);
}

void Motor::control2(unsigned short level)
{
	motor2.control(level);
}

void Motor::control3(unsigned short level)
{
	motor3.control(level);
}

void Motor::control4(unsigned short level)
{
	motor4.control(level);
}

Vector<double> Motor::getSpeed()
{
	//FIXME:这里返回的还不是角速度，而是控制量
	Vector<double> retVal(4);
	retVal(0) = motor1.data;
	retVal(1) = motor2.data;
	retVal(2) = motor3.data;
	retVal(3) = motor4.data;
	return retVal;
}

unsigned short Motor::levelToCtrl(unsigned short level)
{
	unsigned short ctrl = (level <= 0)?0:((level >= 1000)?50000:((1000 + level) * 24));
	return ctrl;
}
