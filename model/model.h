#pragma once

#include "model_defs.h"
#include "math.h"

namespace neuron_model
{

    void getEquilibriumPoint(vector V);


#if MODEL == HODGKIN_HUXLEY
    //ORDER: v,m,h,n

    double exp2(double x);

    inline double func1(vector v)
    {
        double Ik = -36.0 * (v[0] + 12.0) * pow(v[3], 4.0);
        double Ina = -120.0 * (v[0] - 115.0) * pow(v[1], 3.0) * v[2];
        double Il = -0.3 * (v[0] - 10.6);

        return Ik + Ina + Il;
    }

    inline double func2(vector v)
    {
        double am = 0.1 * (25.0 - v[0]) / (exp((25.0 - v[0]) * 0.1) - 1.0);
        double bm = 4.0 * exp(v[0] * -0.0555);

        return am * (1 - v[1]) - bm * v[1];
    }

    inline double func3(vector v)
    {
        double ah = 0.07 * exp(v[0] * -0.05);
        double bh = 1.0 / (exp((30.0 - v[0]) * 0.1) + 1.0);

        return ah * (1 - v[2]) - bh * v[2];
    }

    inline double func4(vector v)
    {
        double an = 0.01 * (10.0 - v[0]) / (exp((10.0 - v[0]) * 0.1) - 1.0);
        double bn = 0.125 * exp(v[0] * -0.0125);

        return an * (1.0 - v[3]) - bn * v[3];
    }

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

