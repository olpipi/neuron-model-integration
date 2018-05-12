#include "MethodEuler.h"


MethodEuler::MethodEuler()
{
}

MethodEuler::~MethodEuler()
{
}

void MethodEuler::nextStep(double *y, double t)
{
	int size;
	double *yPrev;

	size = this->model->getSize();
	yPrev = new double[size];

	for (int j = 0; j < size; j++) yPrev[j] = y[j];
	for (int i = 0; i < size; i++){
		y[i] = yPrev[i] + this->model->getFuncArr()[i](t, y) * this->step;
	}
	y[0] += this->getNoise();
}