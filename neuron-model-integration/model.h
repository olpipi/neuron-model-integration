#ifndef __model__
#define __model__
   

	#define N 2 

	typedef double vector[N];
	typedef double(*funcdef)(double x, vector y);
	typedef funcdef funcarr[N];

	void Model_next_Step(double* V, double Xn, double step, double W, double signal, double noise, int method);

	void setParams(double step, double freq);


#endif