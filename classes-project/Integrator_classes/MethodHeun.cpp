#include "MethodHeun.h"


MethodHeun::MethodHeun()
{
}

MethodHeun::~MethodHeun()
{
}

void MethodHeun::nextStep(double *y, double t)
{
	int size;
	double *yPrev, *v1 ,*v2;
	double noise;

	size  = this->model->getSize();
	yPrev = new double[size];
	v1    = new double[size];
	v2    = new double[size];

	noise = this->getNoise();

	for (int i = 0; i < size; i++) {
		v1[i] = v2[i] = y[i];
		yPrev[i] = this->model->getFuncArr()[i](t - this->step, y);
	}

	for (int i = 0; i < size; i++){
		v1[i] = y[i] + yPrev[i] * step;
		if (i == 0) v1[0] += noise;
		v2[i] = y[i] + 0.5 * (yPrev[i] + this->model->getFuncArr()[i](t, v1)) * this->step;
		if (i == 0) v2[0] += noise;
	}


	for (int i = 0; i < size; i++) y[i] = v2[i];
	y[0] = this->getNoise();
}