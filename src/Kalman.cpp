#include "Kalman.h"

Kalman::Kalman(double xx,double pp,double qq,double rr)
{
}

Kalman::~Kalman()
{
}

pair<double,double> Kalman::operator()(double z)
{
	//更新
	//K=P_{k|k-1}*H'*inv(H*P_{k|k-1}*H'+R)其中H=I
	k = p / (p + r);
	//X_{k|k}=X_{k|k-1}+K*Y=F*X_{k-1|k-1}+K*Y=F*X_{k-1|k-1}+K*(Z-H*F*X_{k-1|k-1})，其中F=I，H=I
	//所以x_{k|k}=x_{k-1|k-1}+k*(z-x_{k-1|k-1})
	x = x + k * (z - x);
	//预测
	//P_{k|k}=P_{k|k-1}-K*H*P_{k|k-1}-P_{k|k-1}*H'*K'+K*(H*P_{k|k-1}*H'+R)*K'
	//其中H=I，所以p_{k|k}=p_{k|k-1}+k*(p_{k|k-1}+r)*k-2*k*p_{k|k-1}
	//因为k*(p_{k|k-1}+r)=p_{k|k-1}所以p_{k|k}=p_{k|k-1}+p_{k|k-1}*k-2*k*p_{k|k-1}=(1-k)*p_{k|k-1}
	//P_{k+1|k}=F*P_{k|k}*F'+Q，其中F=I
	//所以p_{k+1|k} = (1-k)*p_{k|k-1} + q
	p = (1 - k) * p + q;
	return make_pair(x,1-k);
}
