#include <assert.h>
#include "wirish.h"
#include "Motor.h"

Motor __attribute__((init_priority(3))) Motor::motors[4] = {Motor(D28),Motor(D27),Motor(D11),Motor(D12)};
bool Motor::isTimerInit = false;

Motor::Motor(unsigned char p)
:pin(p),data(0)
{
	pinMode(pin,PWM);
	if(false == isTimerInit) {
		Timer3.setPeriod(2080);
		isTimerInit = true;
	}
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
	motors[0].control(level);
}

void Motor::control2(unsigned short level)
{
	motors[1].control(level);
}

void Motor::control3(unsigned short level)
{
	motors[2].control(level);
}

void Motor::control4(unsigned short level)
{
	motors[3].control(level);
}

Vector<double> Motor::getSpeed()
{
	//FIXME:这里返回的还不是角速度，而是控制量
	Vector<double> retVal(4);
	for(int i = 0 ; i < 4 ; i++) retVal(i) = motors[i].data;
	return retVal;
}

unsigned short Motor::levelToCtrl(unsigned short level)
{
	unsigned short ctrl = (level <= 0)?0:((level >= 1000)?50000:((1000 + level) * 24));
	return ctrl;
}
