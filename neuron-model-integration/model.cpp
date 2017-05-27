#include <mathimf.h>
#include "model.h"
#include "Runge_Kutta.h"	
#include "Euler_Maruyama.h"
#include "Heun.h"


/*----------!!!! ORDER: v,m,h,n !!!!------------*/



double funcv(double x, vector y);
double funcm(double x, vector y);
double funch(double x, vector y);
double funcn(double x, vector y);

double SIG = 0;

double step = 0.01;
double W = 0;
double signalCoef = 0;

funcarr functions = { *funcv, *funcm, *funch, *funcn };

void setParams(double signal, double step, double freq){
	W = freq;
	SIG = signal;
	::step = step;
	signalCoef = 2 * 3.14159 * 0.001 * freq;
}



void Model_next_Step(double* Vn, double Xn, double st, double w, double signal, double noise) {
	//step = st;
	//W = w;

	//SIG = signal;

		
	//if (method == 1){
		heun(Vn, Xn, step, functions, noise);
	//}
	/*if (method == 2){
		euler_Maruyama(Vn, Xn, step, functions, noise);
	}
	if (method == 3){
		Runge_Kutta_fourth_order(Vn, Xn, step, functions);
		Vn[0] += noise;
	}*/
}

 double exp2(double x) {
	x = 1.0 + x / 1024;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x; x *= x; x *= x;
	x *= x; x *= x;
	return x;
}

double sig(double x){
	if (SIG == 0) return 0;
	double s = 0;
	if (SIG < 0) s = -SIG * sin(2 * 3.14 * W * x * 0.001);
	else s = SIG;
	return s;
}

double funcv(double x, vector y){
	double v;

	double Ik = -36.0 * (y[0] + 12.0)  * pow(y[3], 4);
	double Ina = -120.0 * (y[0] - 115.0) * pow(y[1], 3) * y[2];
	double Il = -0.3  * (y[0] - 10.6);

	v = Ik + Ina + Il + SIG * sin(x * signalCoef);
	return v;
}
double funcm(double x, vector y){
	double m;

	double am = 0.1 * (25.0 - y[0]) / (exp2((25.0 - y[0]) * 0.1) - 1.0);
	double bm = 4.0 * exp2(y[0] * -0.0555555555);
	m = am * (1 - y[1]) - bm * y[1];
	return m;
}
double funch(double x, vector y){
	double h;

	double ah = 0.07 * exp2(y[0] * -0.05);
	double bh = 1.0 / (exp2((30.0 - y[0]) * 0.1) + 1);

	h = ah * (1.0 - y[2]) - bh * y[2];
	return h;
}
double funcn(double x, vector y){
	double n;

	double an = 0.01 * (10.0 - y[0]) / (exp2((10.0 - y[0]) * 0.1) - 1.0);
	double bn = 0.125 * exp2(y[0] * -0.0125);

	n = an * (1 - y[3]) - bn * y[3];
	return n;
}







/*double funcv(double x, vector y){
	double v;
	const double Gk  =   36;
	const double Gna =  120;
	const double Gl  =  0.3;
	const double Vk  =  -12;
	const double Vna =  115;
	const double Vl  = 10.6;


	double Ik  = -Gk  * (y[0] - Vk)  * pow(y[3], 4);
	double Ina = -Gna * (y[0] - Vna) * pow(y[1], 3) * y[2];
	double Il  = -Gl  * (y[0] - Vl);

	v = Ik + Ina + Il + sig(x);
	return v;
}


double funcm(double x, vector y){
	double m;
	const double am0 = 0.1;
	const double v1  =  25;
	const double vm1 =  10;
	const double bm0 =   4;
	const double vm2 =  18;

	double am = am0 * (v1 - y[0]) / (exp((v1 - y[0]) / vm1) - 1);
	double bm = bm0 * exp(-y[0] / vm2);
	m = am * (1 - y[1]) - bm * y[1];
	return m;
}
double funch(double x, vector y){
	double h;
	const double ah0 = 0.07;
	const double vh1 =   20;
	const double bh0 =    1;
	const double v2  =   30;
	const double vh2 =   10;

	double ah = ah0 * exp(-y[0] / vh1);
	double bh = bh0 / (exp((v2 - y[0]) / vh2) + 1);

	h = ah * (1 - y[2]) - bh * y[2];
	return h;
}
double funcn(double x, vector y){
	double n;
	const double an0 =  0.01;
	const double v3  =    10;
	const double vn1 =    10;
	const double bn0 = 0.125;
	const double vn2 =    80;

	double an = an0 * (v3 - y[0]) / (exp((v3 - y[0]) / vn1) - 1);
	double bn = bn0 * exp(-y[0] / vn2);

	n = an * (1 - y[3]) - bn * y[3];
	return n;
}*/

