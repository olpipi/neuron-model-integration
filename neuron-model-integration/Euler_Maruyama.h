#ifndef __Euler_Maruyama__
#define __Euler_Maruyama__

#define N 4 

typedef double vector[N];
typedef double(*funcdef)(double x, vector y);
typedef funcdef funcarr[N];

void euler_Maruyama(double *Yn, double Xn, double step, funcarr func, double noise);

#endif