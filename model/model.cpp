
#include "model.h"
#include <math.h>


namespace neuron_model
{

#if MODEL == HODGKIN_HUXLEY

    void getEquilibriumPoint(neuron_model::vector V)
    {
        V[0] = 0.000277;
        V[1] = 0.0529;
        V[2] = 0.5961;
        V[3] = 0.3177;
    }

    inline double exp2(double x)
    {
        x = 1.0 + x / 1024;
        x *= x; x *= x; x *= x; x *= x;
        x *= x; x *= x; x *= x; x *= x;
        x *= x; x *= x;
        return x;
    }



#elif MODEL == FITZHUGH_NAGUMO

    void getEquilibriumPoint(vector V)
    {
        V[0] = -1.1;
        V[1] = -0.656;
    }

#endif

}
