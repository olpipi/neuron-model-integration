#ifndef __Runge_Kutta__
#define __Runge_Kutta__

#define N 2 

typedef double vector[N];
typedef double (*funcdef)(double x, vector y);
typedef funcdef funcarr[N];

void Runge_Kutta_fourth_order(double *Yn, double Xn, double step, funcarr func);

#endif