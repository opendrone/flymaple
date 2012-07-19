#ifndef GLOBALXYZ_H
#define GLOBALXYZ_H

#include "Vector.h"

class GlobalXYZ {
	//全局坐标系的xyz
	Vector<double> X;
	Vector<double> Y;
	Vector<double> Z;
	unsigned int timestamp;
	void getZ(Vector<double> & newZ,Vector<double> & deltaTheta);
	void getX(const Vector<double> & newZ,Vector<double> & newX,Vector<double> & deltaTheta);
	void getY(const Vector<double> & newX,const Vector<double> & newZ,Vector<double> & newY);
	void update(const Vector<double> & newX,const Vector<double> & newY,const Vector<double> & newZ);
public:
	GlobalXYZ();
	~GlobalXYZ();
	//获得全局坐标系的X,Y,Z的在体坐标系中的向量
	void getXYZ(Vector<double> & X,Vector<double> & Y,Vector<double> & Z);
	//获得飞机的滚动角，俯仰角，偏航角
	void getRPY(double & roll,double & pitch,double & yaw);
};

#endif
