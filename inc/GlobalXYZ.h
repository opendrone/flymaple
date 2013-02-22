#ifndef GLOBALXYZ_H
#define GLOBALXYZ_H

/**
 * @file   GlobalXYZ.h
 * @author breadbread1984 <breadbread1984@163.com>
 * @date   Sat Jul 21 15:12:00 2012
 * 
 * @brief	The static class for calculating the axes of the global frame represented in the body frame. 
 * 
 * @copyright GPLv3 
 */

#include "Vector.h"
#include "Sensor.h"

class GlobalXYZ {
	static GlobalXYZ xyz;
	/**
	 * Constructor initializing the GlobalXYZ.
	 * To do the initialization for only once, the constructor is hide from developer.
	 * The only one GlobalXYZ object is a static one created automatically.
	 */
	GlobalXYZ();
	//全局坐标系的xyz
	static Vector<double> X;
	static Vector<double> Y;
	static Vector<double> Z;
	static unsigned int timestamp;
	void getZ(Vector<double> & newZ,Vector<double> & deltaTheta);
	void getX(const Vector<double> & newZ,Vector<double> & newX,Vector<double> & deltaTheta);
	void getY(const Vector<double> & newX,const Vector<double> & newZ,Vector<double> & newY);
	void update(const Vector<double> & newX,const Vector<double> & newY,const Vector<double> & newZ);
public:
	/**
	 * Destructor.
	 */
	~GlobalXYZ();
	/**
	 * Get the axes of the global frame represented in the body frame.
	 * 
	 * @param X is the X axis of the global frame represented in the body frame.
	 * @param Y is the Y axis of the global frame represented in the body frame.
	 * @param Z is the Z axis of the global frame represented in the body frame.
	 */
	//获得全局坐标系的X,Y,Z的在体坐标系中的向量
	static void getXYZ(Vector<double> & X,Vector<double> & Y,Vector<double> & Z);
	/**
	 * Get the roll, pitch and yaw angle calculated from the axes of the global frame.
	 * 
	 * @param roll the roll angle.
	 * @param pitch the pitch angle.
	 * @param yaw the yaw angle.
	 * @return the direction cosine matrix.
	 */
	//获得飞机的滚动角，俯仰角，偏航角
	static Matrix<double> getRPY(double & roll,double & pitch,double & yaw);
};

#endif
