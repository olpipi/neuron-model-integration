#include "Method.h"
#include "MethodEuler.h"
#include "MethodHeun.h"
#include "Model.h"
#include "ModelFHN.h"
#include "ModelHH.h"
#include "Solver.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <omp.h>

#define timeMeasurement

#define LAUNCH_TYPE 1 //1 - escapetime (parallel); 2 - simple launch

#define MODEL   1 //
#define METHOD  1 //

#define STEP 0.01
#define TIME 100
#define NUMAVE 50000 
#define SIGNAL 4

/*****Params*****/
#define NOISE_FROM 0.0001
#define NOISE_TO   100
#define NOISE_STEP 1.1

#define FREQ_FROM 10
#define FREQ_TO   140
#define FREQ_STEP 10

/*****Simple Params*****/
#define NOISE 10
#define FREQ  140

void simplelaunch()
{
	std::ofstream fout("output.txt");

	Model *model;
	if (MODEL == 1) model = new ModelHH();
	else            model = new ModelFHN();

	Method *method;
	if (METHOD == 1) method = new MethodHeun();
	else             method = new MethodEuler();

	Solver *solver = new Solver(method, model);
	solver->setParams(TIME, STEP, FREQ, SIGNAL, NOISE);

	solver->launchSimple(&fout);

	delete solver;
	delete model;
	delete method;
	fout.close();
}

void escapeTime()
{
	double noiseIntencity = NOISE_FROM;
	double EscTime, EscTime2;


	for (double frequency = FREQ_FROM; frequency < FREQ_TO; frequency += FREQ_STEP)
	{

		while (noiseIntencity < NOISE_TO)
		{
			EscTime = 0.0;
			EscTime2 = 0.0;
			std::cout << frequency << ":  " << noiseIntencity << "\n";

#pragma omp parallel reduction(+:EscTime,EscTime2) num_threads(omp_get_num_procs())
			{

#pragma omp for
				Model *model;
				if (MODEL == 1) model = new ModelHH();
				else            model = new ModelFHN();

				Method *method;
				if (METHOD == 1) method = new MethodHeun();
				else             method = new MethodEuler();

				Solver *solver = new Solver(method, model);
				solver->setParams(TIME, STEP, FREQ, SIGNAL, NOISE);

				double escTime = solver->launchEscapeTime();

				delete solver;
				delete model;
				delete method;

			}


			noiseIntencity *= NOISE_STEP;
		}

	}
}

int main(){
	if (LAUNCH_TYPE == 1) escapeTime();
	else                  simplelaunch();
	return 0;
}