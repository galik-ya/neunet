#include "../ActivationFunction.h"
#include <iostream>

class ReLuFunction: public ActivationFunction {

public:
    double f(double x) final {
        return std::max(0.0, x);
    }
};