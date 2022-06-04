#include "../ActivationFunction.h"
#include <iostream>
#include <cmath>

class SigmoidFunction: public ActivationFunction {

public:
    double f(double x) final {
        return 1.0 / ( 1.0 + exp(-x) );
    }
};