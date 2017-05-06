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

inline void heun_inline(double* Yn, double Xn, double step, funcarr func, double noise)
{

	vector V, V1, nz, preV;

	nz[0] = noise;
	nz[1] = 0;


	//double x = xPrev - xPrev * xPrev* xPrev * 0.3333333 - V[1] + 0.5 * sin(t * signalCoef);
	//double m = 0.05 * V[0] + 0.055;

	/*for (int i = 0; i < N; i++) {
		V[i] = V1[i] = Yn[i];
		preV[i] = func[i](Xn - step, Yn);
	}*/

	preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.3333333 - Yn[1] + 0.5 * sin((Xn - step) * signalCoef);
	preV[1] = 0.05 * Yn[0] + 0.055;

	V[0] = Yn[0] + preV[0] * step + nz[0];
	V[1] = Yn[1] + preV[1] * step + nz[1];

	double tmp = V[0] - V[0] * V[0] * V[0] * 0.3333333 - V[1] + 0.5 * sin(Xn * signalCoef);
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step + nz[0];
	double tmp1 = 0.05 * V[0] + 0.055;
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp1) * step + nz[0];


	/*for (int i = 0; i < N; i++){
		V[i] = Yn[i] + preV[i] * step + nz[i];
		V1[i] = Yn[i] + 0.5 * (preV[i] + func[i](Xn, &V[0])) * step + nz[i];
	}*/




	for (int i = 0; i < N; i++) Yn[i] = V1[i];
};





void Model_next_Step(double* Vn, double Xn, double st, double w, double signal, double noise, int method) {
	//step = st;
	//W = w;

	//SIG = signal;

		
	//if (method == 1){
	heun_inline(Vn, Xn, step, functions, noise);
	//heun(Vn, Xn, step, functions, noise);
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
