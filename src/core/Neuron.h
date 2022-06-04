#pragma once

#include <iostream>
#include <vector>
#include "Connection.h"
#include "ActivationFunction.h"

using namespace std;

class Neuron {

public:

    explicit Neuron(ActivationFunction* activation, vector<Neuron*>* previous = nullptr);

    ~Neuron() {
        delete next;
    }

    void deleteForward(bool deleteNext);

    vector<OutConnection*>* getOutConnections() { return next; }
    vector<InConnection*>* getInConnections() { return previous; }

    void compute(double input);
    void compute();

    double getInput() const { return input; }
    double getResult() const { return result; }

    ActivationFunction* getActivation() { return activation; }

private:
    ActivationFunction* activation;

    vector<OutConnection*>* next = nullptr;
    vector<InConnection*>* previous = nullptr;

    void addOutConnection(OutConnection* connection);
    void addInConnection(InConnection* connection);

    double input;
    double result;
};