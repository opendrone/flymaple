#ifndef KALMAN_H
#define KALMAN_H

#include <utility>

using namespace std;

class Kalman {
	double p,q,r,k;
	double x;
public:
	Kalman(double xx,double pp = 0,double qq = 1,double rr = 32);
	~Kalman();
	pair<double,double> operator()(double measurement);	//返回滤波结果，和置信百分比
};

#endif
