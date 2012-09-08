#include "wirish.h"
#include "Compass.h"

Compass Compass::compass __attribute__((init_priority(3000)));
const unsigned char Compass::CompassAddress = 0x1e;
const short Compass::sign[3] = {1,1,1};
const double Compass::scale[3] = {1,1.09,1};

Compass::Compass(unsigned char gain)
{
#ifndef NDEBUG
	if(gain > 7) {
		SerialUSB.println("gain should be within [0,7]");
		waitForButtonPress(0);
	}
#endif
	Sensor::write(CompassAddress,0x02,0x00);
	Sensor::write(CompassAddress,0x01,gain << 5);
	Sensor::write(CompassAddress,0x00,0x70);			//正常工作模式
	delay(100);
}

void Compass::getRawReading(short& x,short& y,short& z)
{
	unsigned char buffer[6];
	Sensor::read(CompassAddress,0x03,6,buffer);
    x = (((short)buffer[0]) << 8) | buffer[1];    // X axis
    y = (((short)buffer[4]) << 8) | buffer[5];    // Y axis
    z = (((short)buffer[2]) << 8) | buffer[3];    // Z axis
}

Compass::~Compass()
{
}

Vector<double> Compass::getReading()
{
	short x,y,z;
	compass.getRawReading(x,y,z);
	x = sign[0] * x * scale[0];
	y = sign[1] * y * scale[1];
	z = sign[2] * z * scale[2];
	Vector<double> retVal(3);
	retVal(0) = x;	retVal(1) = y;	retVal(2) = z;
	return retVal;
}

void Compass::calibrate(unsigned char gain)
{
#ifndef NDEBUG
	if(gain > 7) {
		SerialUSB.println("gain should be within [0,7]");
		waitForButtonPress(0);
	}
#endif
	static double maxval,maxx,maxy,maxz;
	static bool isFirstCalibrate = true;
	if(isFirstCalibrate) {
		maxval = maxx = maxy = maxz = 0;
		isFirstCalibrate = false;
	}
	Sensor::write(CompassAddress,0x00,0x11);				//三轴正极大，获得最大值
	Sensor::write(CompassAddress,0x01,gain << 5);
	for(int i = 0 ; i < 10 ; i++) {
		Sensor::write(CompassAddress,0x02,1);
		delay(100);
		short x,y,z;
		compass.getRawReading(x,y,z);
		if(x > maxx) maxx = x; if(maxx > maxval) maxval = maxx;
		if(y > maxy) maxy = y; if(maxy > maxval) maxval = maxy;
		if(z > maxz) maxz = z; if(maxz > maxval) maxval = maxz;
	}
#ifndef NDEBUG
	SerialUSB.print("scalex = "); SerialUSB.print(maxval / maxx); 
	SerialUSB.print(" scaley = "); SerialUSB.print(maxval / maxy);
	SerialUSB.print(" scalez = "); SerialUSB.print(maxval / maxz);
	SerialUSB.println();
#endif
	Sensor::write(CompassAddress,0x00,0x70);
	Sensor::write(CompassAddress,0x02,0);
	delay(100);
}
