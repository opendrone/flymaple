#include "Compass.h"

Compass Compass::compass __attribute__((init_priority(3)));
const unsigned char Compass::CompassAddress = 0x1e;
const short Compass::sign[3] = {1,1,1};

Compass::Compass()
{
	Sensor::write(CompassAddress,0x02,0x00);
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
	x = sign[0] * x;
	y = sign[1] * y;
	z = sign[2] * z;
	Vector<double> retVal(3);
	retVal(0) = x;	retVal(1) = y;	retVal(2) = z;
	return retVal;
}
