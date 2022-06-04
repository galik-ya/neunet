#include "../ActivationFunction.h"
#include <iostream>

class LinearFunction: public ActivationFunction {

public:

    constexpr static double DEFAULT_MULTIPLIER = 1.0;

    explicit LinearFunction(double multiplier = DEFAULT_MULTIPLIER): multiplier(multiplier) { };

    double getMultiplier() const { return multiplier; }

    double f(double x) final {
        return std::clamp(multiplier * (x + multiplier), 0.0, 1.0);
    }


private:
    double multiplier;
};