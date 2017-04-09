#ifndef __Heun__
#define __Heun__

#define N 2 

typedef double vector[N];
typedef double(*funcdef)(double x, vector y);
typedef funcdef funcarr[N];

void heun(double *Yn, double Xn, double step, funcarr func, double noise);

#endif