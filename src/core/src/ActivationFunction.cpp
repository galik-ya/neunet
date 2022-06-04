#include "../ActivationFunction.h"
#include <iostream>

double ActivationFunction::derivative(double x) {

    return (f(x+H) - f(x-H)) / (2.0 * H);
}
