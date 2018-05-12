#include "Model.h"


Model::Model()
{
	int size         = 0;
	double sigRange  = 0;
	double sigCoef   = 0;
	//funcdef *funcArr = nullptr;
}

std::function<double(double, double*)> *Model::getFuncArr()
{
	return this->funcArr;
}

int Model::getSize()
{
	return this->size;
}

double Model::getThresholdValue()
{
	return this->thresholdValue;
}