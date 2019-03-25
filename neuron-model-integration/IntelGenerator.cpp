#include "IntelGenerator.h"
#include "mkl.h"
#include <Windows.h>



WORD getStandartSeed() {
	WORD time;
	SYSTEMTIME* st = new SYSTEMTIME();
	GetSystemTime(st);
	time = st->wMilliseconds;
	delete st;
	return time;
}

// »нициализаци€ генератора
VSLStreamStatePtr InitGen() {
	VSLStreamStatePtr stream;
	WORD BIG_SEED = getStandartSeed();
	const unsigned int seed[2] = { BIG_SEED, BIG_SEED };
	vslNewStreamEx(&stream, VSL_BRNG_MCG59, 2, seed);
	return stream;
}
// ќсвобождение структур данных генератора
void FreeGen(VSLStreamStatePtr stream) {
	vslDeleteStream(&stream);
}
// √енераци€ случайных чисел N(a, b)
// ¬озвращаем массив z из count чисел из нормального распр.
// stream - ссылка на служебную переменную генератора из MKL
void GenerateGauss(double a, double b, int count,
	VSLStreamStatePtr stream, double *z)
{
	// ѕoлучение count случайных чисел и запись их в массив z
	vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, count, z, a, b);
}


void getNoiseArray(double expectedValue, double deviation, int size, double * buffer){
	VSLStreamStatePtr stream = InitGen();
	GenerateGauss(0, deviation, size, stream, buffer);
	FreeGen(stream);
}