#include <cmath>
#include <limits>
#include "wirish_time.h"
#include "Accelerometer.h"
#include "Compass.h"
#include "Gyroscope.h"
#include "GlobalXYZ.h"

using std::sqrt;
using std::numeric_limits;

GlobalXYZ GlobalXYZ::xyz;
Vector<double> GlobalXYZ::X(3);
Vector<double> GlobalXYZ::Y(3);
Vector<double> GlobalXYZ::Z(3);
unsigned int GlobalXYZ::timestamp;

GlobalXYZ::GlobalXYZ()
{
	Vector<double> dTheta;
	//初始化全局坐标系的Z向量
	getZ(Z,dTheta);
	//初始化全局坐标系的X向量
	getX(Z,X,dTheta);
	//初始化全局坐标系的Y向量
	getY(X,Z,Y);
	//设置时间戳
	timestamp = micros();
}

GlobalXYZ::~GlobalXYZ()
{
}

void GlobalXYZ::getZ(Vector<double> & newZ,Vector<double> & deltaTheta)
{
	Vector<double> accOfG = Accelerometer::getReading();
	double modulus = sqrt(accOfG(0) * accOfG(0) + accOfG(1) * accOfG(1) + accOfG(2) * accOfG(2));
	newZ = Vector<double>(3);
	newZ(0) = -accOfG(0) / modulus;
	newZ(1) = -accOfG(1) / modulus;
	newZ(2) = -accOfG(2) / modulus;
	Vector<double> dZ = newZ - Z;
	deltaTheta = cross_prod(Z,dZ);
}

void GlobalXYZ::getX(const Vector<double> & newZ,Vector<double> & newX,Vector<double> & deltaTheta)
{
	Vector<double> northMagneticPole = Compass::getReading();
	Vector<double> north(3);
	north(0) = northMagneticPole(0); north(1) = northMagneticPole(1);
	north(2) = - (north(0) * newZ(0) + north(1) * newZ(1)) / newZ(2);
	double modulus = sqrt(north(0) * north(0) + north(1) * north(1) + north(2) * north(2));
	newX = Vector<double>(3);
	newX(0) = north(0) / modulus;
	newX(1) = north(1) / modulus;
	newX(2) = north(2) / modulus;
	Vector<double> dX = newX - X;
	deltaTheta = cross_prod(X,dX);
}

void GlobalXYZ::getY(const Vector<double> & newX,const Vector<double> & newZ,Vector<double> & newY)
{
	newY = cross_prod(newZ,newX);
	double modulus = sqrt(newY(0) * newY(0) + newY(1) * newY(1) + newY(2) * newY(2));
	newY(0) = newY(0) / modulus;
	newY(1) = newY(1) / modulus;
	newY(2) = newY(2) / modulus;
}

inline void GlobalXYZ::update(const Vector<double> & newX,const Vector<double> & newY,const Vector<double> & newZ)
{
	//更新状态
	X = newX; Y = newY; Z = newZ;
}

void GlobalXYZ::getXYZ(Vector<double> & retValX,Vector<double> & retValY,Vector<double> & retValZ)
{
	//计算与上次时间戳之间的时间
	unsigned int newtimestamp = micros();
	double dt = ((newtimestamp > timestamp)?(newtimestamp - timestamp):(numeric_limits<unsigned int>::max() - timestamp + newtimestamp)) * 1.0 / 1e6;
	//计算XYZ三轴
	Vector<double> newZ,newX,newY;
	Vector<double> dThetaComp,dThetaAcc,dThetaGyro;
	xyz.getZ(newZ,dThetaAcc);
	xyz.getX(newZ,newX,dThetaComp);
	xyz.getY(newX,newZ,newY);
	Vector<double> angularSpd = Gyroscope::getReading();
	dThetaGyro = angularSpd * dt;
	//融合
	Vector<double> sum;
	sum = dThetaAcc + dThetaComp;
	sum = sum + dThetaGyro;
	Vector<double> dTheta = sum / 3;
	//计算返回值
	Vector<double> dX,dY,dZ;
	dX = cross_prod(dTheta,X);
	dY = cross_prod(dTheta,Y);
	dZ = cross_prod(dTheta,Z);
#if 1
	//融合版本
	retValX = X + dX; retValY = Y + dY; retValZ = Z + dZ;
#else
	//没有融合版本
	retValX = newX; retValY = newY; retValZ = newZ;
#endif
	//更新状态
	xyz.update(newX,newY,newZ);
	//更新时间戳
	timestamp = micros();
}

void GlobalXYZ::getRPY(double & roll,double & pitch,double & yaw)
{
	Matrix<double> DCM(3,3);
	Vector<double> newX,newY,newZ;
	getXYZ(newX,newY,newZ);
	//计算体坐标系->全局坐标系的转换矩阵
	DCM(0,0) = newX(0);	DCM(0,1) = newX(1);	DCM(0,2) = newX(2);
	DCM(1,0) = newY(0);	DCM(1,1) = newY(1);	DCM(1,2) = newY(2);
	DCM(2,0) = newZ(0);	DCM(2,1) = newZ(1);	DCM(2,2) = newZ(2);
	//计算返回值
	roll = -atan2(DCM(2,1),DCM(2,2));
	pitch = asin(DCM(2,0));
	yaw = atan2(DCM(1,0),DCM(0,0));
}
