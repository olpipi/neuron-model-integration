#pragma once
#include "Method.h"
#include "MethodEuler.h"
#include "MethodHeun.h"
#include "Model.h"
#include "ModelFHN.h"
#include "ModelHH.h"
#include <fstream>
#include <math.h>

class Solver
{
public:
	Solver();
	Solver(Method *methodA, Model *modelA);
	~Solver();

	void setModel(Model *modelA);
	void setMethod(Method *methodA);
	void setParams(double time, double step, double freq, double sig, double noise);

	double launchEscapeTime();
	void launchSimple(std::ofstream *output);
	bool isGenerating();

private:
	void setModelParams();
	void setMethodParams();

	Method *method;
	Model  *model;

	double denerateTime;
	double step;
	double sigFreq;
	double sigRange;
	double noiseIntensity;
};

