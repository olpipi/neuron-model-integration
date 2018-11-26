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


void setParams(double step, double freq){
	W = freq;
	::step = step;
	signalCoef = freq;
}

inline void heun_inline(double* Yn, double Xn, double step, double noise)
{

	vector V, V1, nz, preV;

	nz[0] = noise;
	nz[1] = 0;

	preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.333 - Yn[1] + 0.5 * sin((Xn - step) * signalCoef);
	preV[1] = 0.05 * Yn[1] + 0.055;

	V[0] = Yn[0] + preV[0] * step + nz[0];
	V[1] = Yn[1] + preV[1] * step + nz[1];

	double tmp = V[0] - V[0] * V[0] * V[0] * 0.333 - V[1] + 0.5 * sin(Xn * signalCoef);
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step + nz[0];
	double tmp1 = 0.05 * V[0] + 0.055;
	V1[1] = Yn[1] + 0.5 * (preV[0] + tmp1) * step;


	for (int i = 0; i < N; i++) Yn[i] = V1[i];
};


void heun1(double* Yn, double Xn, double step, double noise) 
{

    vector V, V1, preV;


    preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.333 - Yn[1] + SIG * sin((Xn - step) * signalCoef);
    preV[1] = 0.05 * Yn[0] + 0.055;;

    V[0] = Yn[0] + preV[0] * step + noise;
    V[1] = Yn[1] + preV[1] * step;


    double tmp = V[0] - V[0] * V[0] * V[0] * 0.333 - V[1] + SIG * sin(Xn * signalCoef);
    V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step + noise;
    
    double tmp1 = 0.05 * V[0] + 0.055;
    V1[1] = Yn[1] + 0.5 * (preV[1] + tmp1) * step;

    Yn[0] = V1[0];
    Yn[1] = V1[1];
}







void Model_next_Step(double* Vn, double Xn, double st, double w, double signal, double noise, int method) {
    SIG = signal;
    //heun_inline(Vn, Xn, step, noise);
    heun1(Vn, Xn, step, noise);
}


double funcX(double t, vector V){
	double x;
	double xPrev = V[0];
	x = xPrev - xPrev * xPrev* xPrev * 0.333 - V[1] + 0.5 * sin(t * signalCoef);
	return x;
}
double funcY(double tx, vector V){
	double m = 0.05 * V[0] + 0.055;
	return m;
}
