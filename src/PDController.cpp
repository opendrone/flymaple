#include "PDController.h"
#include "GlobalXYZ.h"
#include "Pressure.h"

PDController PDController::pd;
double PDController::error_h_old = 0,PDController::error_roll_old = 0,PDController::error_pitch_old = 0,PDController::error_yaw_old = 0;
double PDController::Kzp = 1,PDController::Kzd = 1,PDController::Krp = 1,PDController::Krd = 1,PDController::Kpp = 1,PDController::Kpd = 1,PDController::Kyp = 1,PDController::Kyd = 1;

PDController::PDController()
{
}

PDController::~PDController()
{
}

void PDController::balance(int dh,double droll,double dpitch,double dyaw,double dt)
{
	double roll,pitch,yaw;
	GlobalXYZ::getRPY(roll,pitch,yaw);
	Vector<double> pressure = Pressure::getReading();
	double error_h_new = dh - pressure(2);
	double error_roll_new = droll - roll;
	double error_pitch_new = dpitch - pitch;
	double error_yaw_new = dyaw - yaw;
	
	double ddz = Kzp * error_h_new + Kzd * (error_h_new - error_h_old) / dt;
	double ddroll = Krp * error_roll_new + Krd * (error_roll_new - error_roll_old) / dt;
	double ddpitch = Kpp * error_pitch_new + Kpd * (error_pitch_new - error_pitch_old) / dt;
	double ddyaw = Kyp * error_yaw_new + Kyd * (error_yaw_new - error_yaw_old) / dt;
	
	//TODO
	
	error_h_old = error_h_new;
	error_roll_old = error_roll_new;
	error_pitch_old = error_pitch_new;
	error_yaw_old = error_yaw_new;
}
