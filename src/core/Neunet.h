#pragma once

#include <iostream>
#include <vector>
#include "ActivationFunction.h"
#include "functions/BinaryFunction.hpp"
#include "functions/LinearFunction.hpp"
#include "functions/SigmoidFunction.hpp"
#include "functions/HyperbolicTangentFunction.hpp"
#include "functions/ReLuFunction.hpp"
#include "Neuron.h"

using namespace std;

class Neunet {

public:
    Neunet(const vector<int>& layersNum, ActivationFunction* activation, bool bias);

    ~Neunet();

    vector<double>* compute(vector<double>& input);

    vector<vector<Neuron*>*>* getLayers() { return layers; }

    ActivationFunction* getActivation() { return activation; }

    bool getBias() const { return bias; }

    void print();

private:
    ActivationFunction* activation;

    vector<vector<Neuron*>*>* layers = nullptr;

    bool bias;
};