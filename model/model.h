#pragma once

#include "model_defs.h"

namespace neuron_model
{

    void getEquilibriumPoint(vector V);


#if MODEL == HODGKIN_HUXLEY
    //ORDER: v,m,h,n

#elif MODEL == FITZHUGH_NAGUMO
    //ORDER: x, y

    inline double func1(vector v)
    {
        return (v[0]) - (v[0]) * (v[0]) * (v[0]) * 0.3333 - (v[1]);
    }
    inline double  func2(vector v) {
        return 0.05 * (v[0]) + 0.055;
    }

#endif
}

