#pragma once

#include "model_defs.h"

namespace neuron_model
{

    void getEquilibriumPoint(vector V);


#if MODEL == HODGKIN_HUXLEY
    //ORDER: v,m,h,n

    inline double func1(vector v)
    {
        double _v;
        const double Gk = 36;
        const double Gna = 120;
        const double Gl = 0.3;
        const double Vk = -12;
        const double Vna = 115;
        const double Vl = 10.6;


        double Ik = -Gk * (v[0] - Vk)  * pow(v[3], 4);
        double Ina = -Gna * (v[0] - Vna) * pow(v[1], 3) * v[2];
        double Il = -Gl * (v[0] - Vl);

        _v = Ik + Ina + Il;//add signal sig(x);
        return _v;
    }

    inline double func2(vector v)
    {
        double m;
        const double am0 = 0.1;
        const double v1 = 25;
        const double vm1 = 10;
        const double bm0 = 4;
        const double vm2 = 18;

        double am = am0 * (v1 - v[0]) / (exp((v1 - v[0]) / vm1) - 1);
        double bm = bm0 * exp(-v[0] / vm2);
        m = am * (1 - v[1]) - bm * v[1];
        return m;
    }

    inline double func3(vector v)
    {
        double h;
        const double ah0 = 0.07;
        const double vh1 = 20;
        const double bh0 = 1;
        const double v2 = 30;
        const double vh2 = 10;

        double ah = ah0 * exp(-v[0] / vh1);
        double bh = bh0 / (exp((v2 - v[0]) / vh2) + 1);

        h = ah * (1 - v[2]) - bh * v[2];
        return h;
    }

    inline double func4(vector v)
    {
        double n;
        const double an0 = 0.01;
        const double v3 = 10;
        const double vn1 = 10;
        const double bn0 = 0.125;
        const double vn2 = 80;

        double an = an0 * (v3 - v[0]) / (exp((v3 - v[0]) / vn1) - 1);
        double bn = bn0 * exp(-v[0] / vn2);

        n = an * (1 - v[3]) - bn * v[3];
        return n;
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

