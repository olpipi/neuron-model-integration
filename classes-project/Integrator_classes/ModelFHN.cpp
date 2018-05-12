#include "ModelFHN.h"


ModelFHN::ModelFHN()
{
	this->size = 2;
	this->setFuncArray();

	this->sigCoef  = 0;
	this->sigRange = 0;
	this->thresholdValue = 1;
}

ModelFHN::~ModelFHN()
{
	delete[] this->funcArr;
}

void ModelFHN::setFuncArray()
{
	this->funcArr = new std::function<double(double, double*)> [size];
	this->funcArr[0] = [this](double t, double* y)
	{
		return this->funcv(t, y);
	};
	this->funcArr[1] = [this](double t, double* y)
	{
		return this->funcw(t, y);
	};
	/*this->funcArr[0] = (Model::funcdef)&ModelFHN::funcv;
	this->funcArr[1] = (Model::funcdef)&ModelFHN::funcw;*/
}

void ModelFHN::setInitParams(double signal, double freq)
{
	this->sigRange = signal;
	this->sigCoef  = freq;
}

void ModelFHN::setEquilibrium(double *V)
{
	V[0] = -1.1;
	V[1] = -0.656;
}

double ModelFHN::funcv(double t, double* y)
{
	double x;
	double xPrev = y[0];
	x = xPrev - xPrev * xPrev* xPrev * 0.3333333 - y[1] + this->sigRange * sin(t * this->sigCoef);
	return x;
}

double ModelFHN::funcw(double t, double* y)
{
	double w = 0.05 * y[0] + 0.055;
	return w;
}
