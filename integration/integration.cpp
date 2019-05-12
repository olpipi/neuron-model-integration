// Intergration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "integration.h"
#include "model.h"
#include <math.h>

double step;
double freq;
double ampl;

void setDefaultPoint(double* V)
{
    neuron_model::getEquilibriumPoint(V);
}

void setParams(double _step, double _freq, double _ampl)
{
    step = _step;
    freq = _freq;
    ampl = _ampl;
}
void heun(double* Yn, double Xn, double noise);

void Model_next_Step(double* V, double t, double noise)
{
    heun(V, t, noise);
}

#if MODEL == HODGKIN_HUXLEY

#elif MODEL == FITZHUGH_NAGUMO


void heun(double* Yn, double Xn, double noise)
{
    neuron_model::vector V, V1, preV;

    preV[0] = neuron_model::func1(Yn) + ampl * sin((Xn - step) * freq);
    preV[1] = neuron_model::func2(Yn);
    //preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.333 - Yn[1] + ampl * sin((Xn - step) * freq);
    //preV[1] = 0.05 * Yn[0] + 0.055;

    V[0] = Yn[0] + preV[0] * step;
    V[1] = Yn[1] + preV[1] * step;

    double tmp = neuron_model::func1(V) + ampl * sin(Xn * freq);
    V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step;
    //double tmp = V[0] - V[0] * V[0] * V[0] * 0.333 - V[1] + ampl * sin(Xn * freq);
    //V1[0] = Yn[0] + 0.5 * (preV[0] + tmp) * step;

    double tmp1 = neuron_model::func2(V);
    V1[1] = Yn[1] + 0.5 * (preV[1] + tmp1) * step;
    //double tmp1 = 0.05 * V[0] + 0.055;
    //V1[1] = Yn[1] + 0.5 * (preV[1] + tmp1) * step;

    Yn[0] = V1[0] + noise;
    Yn[1] = V1[1];
}

#endif