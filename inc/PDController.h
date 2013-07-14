#ifndef PDCONTROLLER_H
#define PDCONTROLLER_H

class PDController {
	static PDController pd;
  
	static double error_h_old,error_roll_old,error_pitch_old,error_yaw_old;
	static double Kzp,Kzd,Krp,Krd,Kpp,Kpd,Kyp,Kyd;

	PDController();
public:
	~PDController();
	static void balance(int dh,double droll,double dpitch,double dyaw,double dt);
};

#endif
