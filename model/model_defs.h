#pragma once


#define HODGKIN_HUXLEY  1
#define FITZHUGH_NAGUMO 2

#ifndef MODEL
#define MODEL 1
#endif

namespace neuron_model
{

#if MODEL == HODGKIN_HUXLEY
#define N 4
#define MODEL_NAME "Hodgkin-Huxley model"
#elif MODEL == FITZHUGH_NAGUMO
#define N 2
#define MODEL_NAME "Fitzhugh-Nagumo model"
#endif

    typedef double vector[N];
    typedef double(*funcdef)(double x, vector y);
    typedef funcdef funcarr[N];
}
