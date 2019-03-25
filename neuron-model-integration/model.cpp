#include "model.h"
#include <math.h>

/*----------!!!! ORDER: v,m,h,n !!!!------------*/



double funcX(double t, vector V);
double funcY(double t, vector V);


#define func1(x, y, A, w, t, noise) \
    (x) - (x) * (x) * (x) * 0.333 - (y) + A * sin(t * w)
#define func2(x, y) \
    0.05 * x + 0.055

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

	preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.3333333 - Yn[1] + 0.5 * sin((Xn - step) * signalCoef);
	preV[1] = 0.05 * Yn[0] + 0.055;

	V[0] = Yn[0] + preV[0] * step + nz[0];
	V[1] = Yn[1] + preV[1] * step + nz[1];

	double tmp = V[0] - V[0] * V[0] * V[0] * 0.3333333 - V[1] + 0.5 * sin(Xn * signalCoef);
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step + nz[0];
	double tmp1 = 0.05 * V[0] + 0.055;
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp1) * step + nz[0];


	for (int i = 0; i < N; i++) Yn[i] = V1[i];
};


void heun1(double* Yn, double Xn, double step, double noise)
{

	vector V, V1, preV;



	preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.333 - Yn[1] + SIG * sin((Xn - step) * signalCoef);
	preV[1] = 0.05 * Yn[0] + 0.055;

	V[0] = Yn[0] + preV[0] * step;
	V[1] = Yn[1] + preV[1] * step;


	double tmp = V[0] - V[0] * V[0] * V[0] * 0.333 - V[1] + SIG * sin(Xn * signalCoef);
	V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step;

	double tmp1 = 0.05 * V[0] + 0.055;
	V1[1] = Yn[1] + 0.5 * (preV[1] + tmp1) * step;

	Yn[0] = V1[0] + noise;
	Yn[1] = V1[1];
}

void heun2(double* Yn, double Xn, double step, double noise)
{

    vector V, V1, preV;
    vector K1, K2, res;

    K1[0] = func1(Yn[0], Yn[1], SIG, signalCoef, Xn - step, noise);
    K1[1] = func2(Yn[0], Yn[1]);

    K2[0] = func1(Yn[0] + step * K1[0], Yn[1] + step * K1[1], SIG, signalCoef, Xn, noise);
    K2[1] = func2(Yn[0] + step * K1[0], Yn[1] + step * K1[1]);


    Yn[0] = Yn[0] + 0.5 * step * (K1[0] + K2[0]) + noise;
    Yn[1] = Yn[1] + 0.5 * step * (K1[1] + K2[1]);
}


void Model_next_Step(double* Vn, double Xn, double st, double w, double signal, double noise, int method) {
	SIG = signal;
	heun1(Vn, Xn, step, noise);

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
