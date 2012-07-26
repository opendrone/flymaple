#include "Accelerometer.h"
#include "Compass.h"
#include "Gyroscope.h"
#include "GlobalXYZ.h"
#include "Interfaces4C.h" 

void getReadingFromAcc(double * data)
{
	Vector<double> retVal = Accelerometer::getReading();
	data[0] = retVal(0);
	data[1] = retVal(1);
	data[2] = retVal(2);
}

void getReadingFromComp(double * data)
{
	Vector<double> retVal = Compass::getReading();
	data[0] = retVal(0);
	data[1] = retVal(1);
	data[2] = retVal(2);
}

void getReadingFromGyro(double * data)
{
	Vector<double> retVal = Gyroscope::getReading();
	data[0] = retVal(0);
	data[1] = retVal(1);
	data[2] = retVal(2);
}

void getXYZ(double * X,double * Y,double * Z)
{
	Vector<double> x,y,z;
	GlobalXYZ::getXYZ(x,y,z);
	X[0] = x(0); X[1] = x(1); X[2] = x(2);
	Y[0] = y(0); Y[1] = y(1); Y[2] = y(2);
	Z[0] = z(0); Z[1] = z(1); Z[2] = z(2);
}

void getRPY(double * r,double * p,double * y)
{
	double roll = 0,pitch = 0,yaw = 0;
	GlobalXYZ::getRPY(roll,pitch,yaw);
	*r = roll; *p = pitch; *y = yaw;
}
