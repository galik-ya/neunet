#include "../ActivationFunction.h"
#include <iostream>

class BinaryFunction: public ActivationFunction {

public:

    constexpr static double DEFAULT_THRESHOLD = 0.0;

    explicit BinaryFunction(double threshold = DEFAULT_THRESHOLD): threshold(threshold) { };

    double getThreshold() const { return threshold; }

    double f(double x) final {
        if(x < threshold || std::abs(x - threshold) < EPS)
            return 0.0;
        else
            return 1.0;
    }


private:
    double threshold;
};