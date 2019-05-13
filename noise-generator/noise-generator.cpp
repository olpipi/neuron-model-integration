#include "noise-generator.h"
#include <Windows.h>
#include "pch.h"


WORD getStandartSeed() {
    WORD time;
    SYSTEMTIME* st = new SYSTEMTIME();
    GetSystemTime(st);
    time = st->wMilliseconds;
    delete st;
    return time;
}

VSLStreamStatePtr InitGen() {
    VSLStreamStatePtr stream;
    WORD BIG_SEED = getStandartSeed();
    const unsigned int seed[2] = { BIG_SEED, BIG_SEED };
    vslNewStreamEx(&stream, VSL_BRNG_MCG59, 2, seed);
    return stream;
}
void FreeGen(VSLStreamStatePtr stream) {
    vslDeleteStream(&stream);
}
void GenerateGauss(double a, double b, int count,
    VSLStreamStatePtr stream, double *z)
{
    vdRngGaussian(VSL_RNG_METHOD_GAUSSIAN_ICDF, stream, count, z, a, b);
}


void getNoiseArray(double expectedValue, double deviation, int size, double * buffer) {
    VSLStreamStatePtr stream = InitGen();
    GenerateGauss(0, deviation, size, stream, buffer);
    FreeGen(stream);
}