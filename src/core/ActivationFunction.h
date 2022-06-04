#pragma once
#include <iostream>

class ActivationFunction {
public:

    /**
     * Equality threshold
     */
    constexpr static double EPS = 1e-12;

    /**
     * Derivative step
     */
    constexpr static double H = 1e-10;

    virtual double f(double x) = 0;

    virtual double derivative(double x) final;

    virtual ~ActivationFunction() = default;
};