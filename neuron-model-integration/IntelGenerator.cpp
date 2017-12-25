#include "IntelGenerator.h"

#include <Windows.h>


double * getNoiseArray(double expectedValue, double deviation, WORD seed, int size){
	double*	arr = new double[size];
	if (seed == 0) {
		seed = getStandartSeed();
	}



	return arr;
}



WORD getStandartSeed() {
	WORD time;
	SYSTEMTIME* st = new SYSTEMTIME();
	GetSystemTime(st);
	time = st->wMilliseconds;
	return time;
}

