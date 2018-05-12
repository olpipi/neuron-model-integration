#pragma once
#include <functional>

class Model
{
public:
	//typedef double(Model::*funcdef)(double x, double* y);
	

	Model();
	virtual ~Model() {}

	virtual void setFuncArray() = 0;
	virtual void setInitParams(double signal, double freq) = 0;
	virtual void setEquilibrium(double *V) = 0;

	std::function<double(double, double*)> *getFuncArr();
	int getSize();
	double getThresholdValue();

protected:

	int size;
	double sigRange;
	double sigCoef;
	double thresholdValue;
	//funcdef *funcArr;
	std::function<double(double, double*)> *funcArr;
};

