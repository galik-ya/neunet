#pragma once
#include <iostream>
#include <map>
#include "../../Neunet.h"
#include "../../ErrorFunction.h"
#include "../../functions/MseFunction.hpp"
#include "../../functions/RootMseFunction.hpp"
#include "../../functions/ArctanFunction.hpp"

using namespace std;

class BackpropMentor {

public:
    BackpropMentor(Neunet* net, ErrorFunction* error, double epsilon, double momentum);
    ~BackpropMentor() {
        delete error;
    }

    void learnEpoch(TrainingEpoch& epoch, double beforeErrorLess);

private:
    Neunet* net;

    ErrorFunction* error;

    double epsilon, momentum;

    map<void*, double> valueMap = map<void*, double>();

    void learn(vector<double>& actual,vector<double>& expected);

    double firstDelta(double actual, double expected, Neuron* neuron);
    double hiddenDelta(Neuron* neuron);
    void adjustWeight(Neuron* neuron);
};