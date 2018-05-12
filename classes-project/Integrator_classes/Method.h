#pragma once
#include"Model.h"
#include "NoiseGenerator.h"


class Method
{
public:
	Method();
	virtual ~Method();

	virtual void nextStep(double *y, double t) = 0;
	void setModel(Model *modelA);
	void setStep(double st);
	void setNoiseParam(double noiseP);

	double getNoise();

protected:
	NoiseGenerator* noiseGen;
	Model* model;
	double step;
	double noiseParam;
};

