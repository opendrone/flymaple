#include "wirish.h"
#include "Accelerometer.h"

Accelerometer Accelerometer::accelerometer __attribute__((init_priority(3)));
const unsigned char Accelerometer::AccelAddress = 0x53;
const unsigned char Accelerometer::XL345_DEVID = 0xe5;
const unsigned char Accelerometer::ADXLREG_BW_RATE = 0x2c;
const unsigned char Accelerometer::ADXLREG_POWER_CTL = 0x2d;
const unsigned char Accelerometer::ADXLREG_DATA_FORMAT = 0x31;
const unsigned char Accelerometer::ADXLREG_DEVID = 0x00;
const unsigned char Accelerometer::ADXLREG_DATAX0 = 0x32;
const unsigned short Accelerometer::GRAVITY = 248;
const short Accelerometer::sign[3] = {1,1,1};
const float Accelerometer::sensitivity = 0.004;
short Accelerometer::offset[3] = {0,0,0};

Accelerometer::Accelerometer()
{
	unsigned char buffer[2];
	Sensor::read(AccelAddress,ADXLREG_DEVID,1,buffer);
	unsigned char dev_id = buffer[0];
	if(dev_id != XL345_DEVID) {
		SerialUSB.println("Error, incorrect xl345 devid!");
		SerialUSB.println("Halting program, hit reset...");
		waitForButtonPress(0);
	}
	Sensor::write(AccelAddress,ADXLREG_POWER_CTL,0x00);	delay(5);	//清零
	Sensor::write(AccelAddress,ADXLREG_POWER_CTL,0xff);	delay(5);	//休眠
	Sensor::write(AccelAddress,ADXLREG_POWER_CTL,0x08); delay(5);	//开启工作
	Sensor::write(AccelAddress,ADXLREG_DATA_FORMAT,0x08); delay(5);	//全精度获得读数
	Sensor::write(AccelAddress,ADXLREG_BW_RATE,0x09); delay(5);		//带宽25hz
	
	//计算误差(静止状态下加速仪应该所有读数是0，如果不为零就是误差)
	float accumulator[] = {0,0,0};
	for(int i = 0 ; i < 100 ; i++) {
		short x,y,z;
		getRawReading(x,y,z);
		accumulator[0] += x;
		accumulator[1] += y;
		accumulator[2] += z;
	}
	for(int i = 0 ; i < 3 ; i++) accumulator[i] /= 100;
	//FIXME:程序假设飞机一开始水平摆放，但是不一定正确
	accumulator[2] -= GRAVITY * sign[2];
	for(int i = 0 ; i < 3 ; i++) offset[i] = accumulator[i];
}

void Accelerometer::getRawReading(short& x,short& y,short& z)
{
	unsigned char buffer[6];
	Sensor::read(AccelAddress,ADXLREG_DATAX0,6,buffer);
	x = (((short)buffer[1]) << 8) | buffer[0];    // X axis
	y = (((short)buffer[3]) << 8) | buffer[2];    // Y axis
    z = (((short)buffer[5]) << 8) | buffer[4];    // Z axis
}

Accelerometer::~Accelerometer()
{
}

Vector<double> Accelerometer::getReading()
{
	short x,y,z;
	accelerometer.getRawReading(x,y,z);
	x = sign[0] * (x - offset[0]);
	y = sign[1] * (y - offset[1]);
	z = sign[2] * (z - offset[2]);
	Vector<double> retVal(3);
	retVal(0) = x * sensitivity;
	retVal(1) = y * sensitivity;
	retVal(2) = z * sensitivity;
	//NOTICE:返回的向量的单位是 g（重力加速度）
	return retVal;
}
