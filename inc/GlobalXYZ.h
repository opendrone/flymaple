#ifndef GLOBALXYZ_H
#define GLOBALXYZ_H

#include "Vector.h"
#include "Sensor.h"

class GlobalXYZ {
	static GlobalXYZ xyz;
	GlobalXYZ();
	//全局坐标系的xyz
	static Vector<double> X;
	static Vector<double> Y;
	static Vector<double> Z;
	static unsigned int timestamp;
	void getX(Vector<double> & newX,Vector<double> & deltaTheta);
	void getZ(Vector<double> & newZ,Vector<double> & deltaTheta);
	void getY(const Vector<double> & newX,const Vector<double> & newZ,Vector<double> & newY);
	void update(const Vector<double> & newX,const Vector<double> & newY,const Vector<double> & newZ);
public:
	~GlobalXYZ();
	//获得全局坐标系的X,Y,Z的在体坐标系中的向量
	static void getXYZ(Vector<double> & X,Vector<double> & Y,Vector<double> & Z);
	//获得飞机的滚动角，俯仰角，偏航角
	static void getRPY(double & roll,double & pitch,double & yaw);
};

#endif
