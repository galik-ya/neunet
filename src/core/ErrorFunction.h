#pragma once
#include <iostream>
#include <vector>
#include "TrainingEpoch.hpp"

using namespace std;

class ErrorFunction {

public:

    virtual ~ErrorFunction() = default;

    virtual double f(vector<double>& actual, vector<double>& expected) = 0;
};