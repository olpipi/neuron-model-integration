#include "Heun.h"


void heun(double* Yn, double Xn, double step, funcarr func, double noise){

	vector V, V1, nz, preV;

	nz[0] = noise;
	nz[1] = nz[2] = nz[3] = 0;

	for (int i = 0; i < N; i++) {
		V[i] = V1[i] = Yn[i];
		preV[i] = func[i](Xn - step, Yn);
	}

	for (int i = 0; i < N; i++){
		V[i] = Yn[i] + preV[i] * step + nz[i];
		V1[i] = Yn[i] + 0.5 * (preV[i] + func[i](Xn, &V[0])) * step + nz[i];
	}


	for (int i = 0; i < N; i++) Yn[i] = V1[i];
}