#include "../ErrorFunction.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class ArctanFunction: public ErrorFunction {

public:
    double f(vector<double>& actual, vector<double>& expected) override {

        double result = 0;

        for (int i = 0; i < actual.size(); i++) {
            result += pow(atan(actual[i] - expected[i]), 2);
        }
        return result / actual.size();
    }
};