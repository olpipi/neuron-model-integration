#ifndef __model__
#define __model__
#include "Runge_Kutta.h"
   
	double sig(double x);
	void Model_next_Step(double* V, double Xn, double step, double W, double signal, double noise, int method);

	void setParams(double step, double freq);


#endif