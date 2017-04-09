#include <math.h>
#include "model.h"
#include "Runge_Kutta.h"	
#include "Euler_Maruyama.h"
#include "Heun.h"


/*----------!!!! ORDER: v,m,h,n !!!!------------*/



double funcX(double t, vector V);
double funcY(double t, vector V);


double SIG = 0;

double step = 0.01;
double W = 0;
double signalCoef = 0;

funcarr functions = { *funcX, *funcY };

void setParams(double step, double freq){
	W = freq;
	::step = step;
	signalCoef = 2 * 3.14159 * 0.001 * freq;
}



void Model_next_Step(double* Vn, double Xn, double st, double w, double signal, double noise, int method) {
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

double sig(double x){
	if (SIG == 0) return 0;
	double s = 0;
	if (SIG < 0) s = -SIG * sin(2 * 3.14 * W * x * 0.001);
	else s = SIG;
	return s;
}

double funcX(double t, vector V){
	double x;
	double xPrev = V[0];
	x = xPrev - xPrev * xPrev* xPrev * 0.3333333 - V[1] + 0.5 * sin(t * signalCoef);
	return x;
}
double funcY(double tx, vector V){
	double m = 0.05 * V[0] + 0.055;
	return m;
}
