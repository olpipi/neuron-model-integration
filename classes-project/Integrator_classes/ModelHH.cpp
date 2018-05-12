#include "ModelHH.h"


ModelHH::ModelHH()
{
	this->size = 4;
	this->setFuncArray();

	this->sigCoef = 0;
	this->sigRange = 0;
	this->thresholdValue = 20;
}

ModelHH::~ModelHH()
{
	delete[] this->funcArr;
}

void ModelHH::setFuncArray()
{
	this->funcArr = new std::function<double(double, double*)>[size];
	this->funcArr[0] = [this](double t, double* y)
	{
		return this->funcv(t, y);
	};

	this->funcArr[1] = [this](double t, double* y)
	{
		return this->funcm(t, y);
	};

	this->funcArr[2] = [this](double t, double* y)
	{
		return this->funch(t, y);
	};

	this->funcArr[3] = [this](double t, double* y)
	{
		return this->funcn(t, y);
	};

	/*this->funcArr = new funcdef[size];

	this->funcArr[0] = (Model::funcdef)&ModelHH::funcv;
	this->funcArr[1] = (Model::funcdef)&ModelHH::funcm;
	this->funcArr[2] = (Model::funcdef)&ModelHH::funch;
	this->funcArr[3] = (Model::funcdef)&ModelHH::funcn;*/
}

void ModelHH::setInitParams(double signal, double freq)
{
	this->sigRange = signal;
	this->sigCoef = 0.006283 * freq;
}

void ModelHH::setEquilibrium(double *V)
{
	V[0] = 0.000277;
	V[1] = 0.0529;
	V[2] = 0.5961;
	V[3] = 0.3177;
}



double ModelHH::funcv(double t, double* y)
{
	double v;

	double Ik = -36.0 * (y[0] + 12.0)  * pow(y[3], 4);
	double Ina = -120.0 * (y[0] - 115.0) * pow(y[1], 3) * y[2];
	double Il = -0.3  * (y[0] - 10.6);

	v = Ik + Ina + Il + this->sigRange * sin(t * this->sigCoef);
	return v;
}

double ModelHH::funcm(double t, double* y)
{
	double m;

	double am = 0.1 * (25.0 - y[0]) / (exp((25.0 - y[0]) * 0.1) - 1.0);
	double bm = 4.0 * exp(y[0] * -0.0555555555);
	m = am * (1 - y[1]) - bm * y[1];
	return m;
}

double ModelHH::funch(double t, double* y)
{
	double h;

	double ah = 0.07 * exp(y[0] * -0.05);
	double bh = 1.0 / (exp((30.0 - y[0]) * 0.1) + 1);

	h = ah * (1.0 - y[2]) - bh * y[2];
	return h;
}

double ModelHH::funcn(double t, double* y)
{
	double n;

	double an = 0.01 * (10.0 - y[0]) / (exp((10.0 - y[0]) * 0.1) - 1.0);
	double bn = 0.125 * exp(y[0] * -0.0125);

	n = an * (1 - y[3]) - bn * y[3];
	return n;
}