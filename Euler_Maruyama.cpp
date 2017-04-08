#include "Euler_Maruyama.h"


void euler_Maruyama(double* Yn, double Xn, double step, funcarr func, double noise){

	vector k[4];
	vector V;


	for (int j = 0; j < N; j++) V[j] = Yn[j];
	for (int i = 0; i < N; i++){
		Yn[i] = V[i] + func[i](Xn, V) * step;
		if (i == 0) Yn[i] += noise;
	}




	/*for (int j = 0; j < N; j++) V[j] = Yn[j];
	for (int i = 0; i < N; i++) {
		k[0][i] = func[i](Xn, (double*)V);
	}

	for (int j = 0; j < N; j++) V[j] = Yn[j] + step * k[0][j] / 2;
	for (int i = 0; i < N; i++) {
		k[1][i] = func[i](Xn + step / 2, V);
	}

	for (int j = 0; j < N; j++) V[j] = Yn[j] + step * k[1][j] / 2;
	for (int i = 0; i < N; i++) {
		k[2][i] = func[i](Xn + step / 2, V);
	}

	for (int j = 0; j < N; j++)	V[j] = Yn[j] + step * k[2][j];
	for (int i = 0; i < N; i++) {
		k[3][i] = func[i](Xn + step, V);
	}

	for (int i = 0; i < N; i++) Yn[i] += step / 6 * (k[0][i] + 2 * k[1][i] + 2 * k[2][i] + k[3][i]);*/
}