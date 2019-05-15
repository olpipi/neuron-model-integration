#include "noise-generator.h"
#include <Windows.h>
#include "pch.h"

VSLStreamStatePtr global_stream;

WORD getStandartSeed() {
    WORD time;
    SYSTEMTIME* st = new SYSTEMTIME();
    GetSystemTime(st);
    time = st->wMilliseconds;
    delete st;
    return time;
}

void InitGen() {
    VSLStreamStatePtr stream;
    WORD BIG_SEED = getStandartSeed();
    const unsigned int seed[2] = { BIG_SEED, BIG_SEED };
    vslNewStreamEx(&stream, VSL_BRNG_MCG59, 2, seed);

    global_stream =  stream;
}
void FreeGen(void) {
    vslDeleteStream(&global_stream);
}
void GenerateGauss(double a, double b, int count,
    VSLStreamStatePtr stream, double *z)
{
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, count, z, a, b);
}


void getNoiseArray(double expectedValue, double deviation, int size, double * buffer) {
    GenerateGauss(expectedValue, deviation, size, global_stream, buffer);
}