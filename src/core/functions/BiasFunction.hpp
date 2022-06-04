#include "../ActivationFunction.h"
#include <iostream>

class BiasFunction: public ActivationFunction {

public:
    double f(double x) final {
        return 1.0;
    }
};