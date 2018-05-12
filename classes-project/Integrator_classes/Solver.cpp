#include "Solver.h"


Solver::Solver()
{
	this->model  = nullptr;
	this->method = nullptr;
	this->denerateTime   = 0;
	this->step           = 0;
	this->sigFreq        = 0;
	this->sigRange       = 0;
	this->noiseIntensity = 0;
}

Solver::Solver(Method *methodA, Model *modelA)
{
	this->model  = modelA;
	this->method = methodA;
	this->denerateTime = 0;
	this->step = 0;
	this->sigFreq = 0;
	this->sigRange = 0;
	this->noiseIntensity = 0;
}

Solver::~Solver()
{
}

void Solver::setModel(Model *modelA)
{
	this->model = modelA;
}

void Solver::setMethod(Method *methodA)
{
	this->method = methodA;
}

void Solver::setMethodParams()
{
	this->method->setModel(this->model);
	this->method->setNoiseParam(sqrt(2 * this->noiseIntensity * this->step));
	this->method->setStep(this->step);
}

void Solver::setModelParams()
{
	this->model->setInitParams(this->sigRange, this->sigFreq);
}

void Solver::setParams(double time, double timeStep, double freq, double sig, double noise)
{
	this->denerateTime = time;
	this->step = timeStep;
	this->sigFreq = freq;
	this->sigRange = sig;
	this->noiseIntensity = noise;
}

void Solver::launchSimple(std::ofstream *output)
{
	this->setMethodParams();
	this->setModelParams();

	double *y = new double[this->model->getSize()];
	double t = 0;

	this->model->setEquilibrium(y);

	for (t = 0; t < this->denerateTime; t += this->step){

		//noise = newnoise();


		//Model_next_Step(V, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);
		this->method->nextStep(y, t);

		*output << t << " " << y[0] << "\n";
	}
	delete[]y;
}

double Solver::launchEscapeTime()
{
	this->setMethodParams();
	this->setModelParams();

	double *y = new double[this->model->getSize()];
	double t = 0;

	this->model->setEquilibrium(y);
	double escTime = 0;

	for (t = 0; t < this->denerateTime; t += this->step){

		//noise = newnoise();


		//Model_next_Step(V, i, STEP, FREQ, SIGNAL, (noise * sqrt(2 * dispercy * STEP)), METHOD);
		this->method->nextStep(y, t);

		if (y[0] > this->model->getThresholdValue())
		{
			escTime = t;
			break;
		}
	}
	delete[]y;
	return escTime;
}

