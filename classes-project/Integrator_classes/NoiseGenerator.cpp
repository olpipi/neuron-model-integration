#include "NoiseGenerator.h"
#include <random>
#include <ctime> 


NoiseGenerator::NoiseGenerator()
{
	srand(time(NULL));
}

NoiseGenerator::~NoiseGenerator()
{
}

double NoiseGenerator::getNoise()
{
	double q, t1, t2, s;
	do{
		t1 = rand() * 0.00006103 - 1;
		t2 = rand() * 0.00006103 - 1;
		s = t1 * t1 + t2 * t2;
	} while ((s) > 1);
	q = t1 * sqrt(-2 * log(s) / s);

	return q;
}
