#include "Method.h"


Method::Method()
{
	this->model = nullptr;
	this->step = 0;
	this->noiseParam = 0;

	this->noiseGen = new NoiseGenerator;
}

Method::~Method()
{
	delete this->noiseGen;
}

void Method::setModel(Model *modelA)
{
	this->model = modelA;
}

void Method::setStep(double st)
{
	this->step = st;
}

void Method::setNoiseParam(double noiseP)
{
	this->noiseParam = noiseP;
}

double Method::getNoise()
{
	double noise;
	noise = this->noiseGen->getNoise();
	noise *= this->noiseParam;
	return noise;
}