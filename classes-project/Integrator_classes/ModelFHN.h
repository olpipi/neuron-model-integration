#pragma once
#include "Model.h"
#include "math.h"


class ModelFHN :
	public Model
{
public:
	ModelFHN();
	~ModelFHN();

	void setFuncArray();
	void setInitParams(double signal, double freq);
	void setEquilibrium(double *V);

	double funcv(double t, double* y);
	double funcw(double t, double* y);
};

