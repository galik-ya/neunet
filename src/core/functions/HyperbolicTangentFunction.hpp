#include "../ActivationFunction.h"
#include <iostream>
#include <cmath>

class HyperbolicTangentFunction: public ActivationFunction {

public:
    double f(double x) final {
        return tanh(x);
    }
};