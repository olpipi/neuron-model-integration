// Intergration.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "integration.h"
#include "model.h"
#include <math.h>

double step;
double freq;
double ampl;
double signalCoef;

void setDefaultPoint(double* V)
{
    neuron_model::getEquilibriumPoint(V);
}

void setParams(double _step, double _freq, double _ampl)
{
    step = _step;
    freq = _freq;
    ampl = _ampl;
    signalCoef = 2 * 3.1416 * freq * 0.001;
}
void heun(double* Yn, double Xn, double noise);

void Model_next_Step(double* V, double t, double noise)
{
    heun(V, t, noise);
}

#if MODEL == HODGKIN_HUXLEY
void heun(double* Yn, double Xn, double noise)
{
    neuron_model::vector V, V1, preV;

    preV[0] = neuron_model::func1(Yn) + ampl * sin((Xn - step) * signalCoef);
    preV[1] = neuron_model::func2(Yn);
    preV[2] = neuron_model::func3(Yn);
    preV[3] = neuron_model::func4(Yn);

    V[0] = Yn[0] + preV[0] * step;
    V[1] = Yn[1] + preV[1] * step;
    V[2] = Yn[2] + preV[2] * step;
    V[3] = Yn[3] + preV[3] * step;

    double tmp1 = neuron_model::func1(V) + ampl * sin(Xn * signalCoef);
    V1[0] = Yn[0] + 0.5 * (preV[0] + tmp1) * step;

    double tmp2 = neuron_model::func2(V);
    V1[1] = Yn[1] + 0.5 * (preV[1] + tmp2) * step;

    double tmp3 = neuron_model::func3(V);
    V1[2] = Yn[2] + 0.5 * (preV[2] + tmp3) * step;

    double tmp4 = neuron_model::func4(V);
    V1[3] = Yn[3] + 0.5 * (preV[3] + tmp4) * step;

    Yn[0] = V1[0] + noise;
    Yn[1] = V1[1];
    Yn[2] = V1[2];
    Yn[3] = V1[3];
}

void heun1(double* Yn, double Xn, double noise) {

    neuron_model::vector V, V1, nz, preV;

    preV[0] = neuron_model::func1(Yn);
    preV[1] = neuron_model::func2(Yn);
    preV[2] = neuron_model::func3(Yn);
    preV[3] = neuron_model::func4(Yn);

    V[0] = Yn[0] + preV[0] * step;
    V[1] = Yn[1] + preV[1] * step;
    V[2] = Yn[2] + preV[2] * step;
    V[3] = Yn[3] + preV[3] * step;

    V1[0] = Yn[0] + 0.5 * (preV[0] + neuron_model::func1(V)) * step;
    V1[1] = Yn[1] + 0.5 * (preV[1] + neuron_model::func2(V)) * step;
    V1[2] = Yn[2] + 0.5 * (preV[2] + neuron_model::func3(V)) * step;
    V1[3] = Yn[3] + 0.5 * (preV[3] + neuron_model::func4(V)) * step;


    for (int i = 0; i < N; i++) Yn[i] = V1[i];
    
}

#elif MODEL == FITZHUGH_NAGUMO


void heun(double* Yn, double Xn, double noise)
{
    neuron_model::vector V, V1, preV;

    preV[0] = neuron_model::func1(Yn) + ampl * sin((Xn) * freq);
    preV[1] = neuron_model::func2(Yn);
    //preV[0] = Yn[0] - Yn[0] * Yn[0] * Yn[0] * 0.333 - Yn[1] + ampl * sin((Xn - step) * freq);
    //preV[1] = 0.05 * Yn[0] + 0.055;

    V[0] = Yn[0] + preV[0] * step;
    V[1] = Yn[1] + preV[1] * step;

    double tmp = neuron_model::func1(V) + ampl * sin((Xn + step) * freq);
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