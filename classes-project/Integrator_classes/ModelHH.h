#pragma once
#include "Model.h"
#include "math.h"

class ModelHH :
	public Model
{
public:
	ModelHH();
	~ModelHH();

	void setFuncArray();
	void setInitParams(double signal, double freq);
	void setEquilibrium(double *V);

private:
	double funcv(double t, double* y);
	double funcm(double t, double* y);
	double funch(double t, double* y);
	double funcn(double t, double* y);
};

