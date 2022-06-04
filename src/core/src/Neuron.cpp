#include <iostream>
#include "../Neuron.h"
#include "../Exception.hpp"
#include "../functions/BiasFunction.hpp"

Neuron::Neuron(ActivationFunction* activation, vector<Neuron*>* previous): activation(activation) {

    if(previous != nullptr) {
        for(Neuron* in : *previous) {
            auto connection = new InOutConnection(in, this);
            addInConnection(connection);
            in->addOutConnection(connection);
        }
    }
}

void Neuron::deleteForward(bool deleteNext) {
    if(next != nullptr && deleteNext)
        for (int i = 0; i < next->size(); i++)
            (*next)[i]->getOut()->deleteForward(i == 0);
    delete this;
}

void Neuron::addOutConnection(OutConnection *connection) {
    if(next == nullptr)
        next = new vector<OutConnection*>();
    next->push_back(connection);
}

void Neuron::addInConnection(InConnection *connection) {
    if(previous == nullptr)
        previous = new vector<InConnection*>();
    previous->push_back(connection);
}

void Neuron::compute() {

    if(previous == nullptr)
        if(dynamic_cast<BiasFunction*>(activation) != nullptr)
            return compute(0.0);
        else
            throw Exception("For input layer must be called compute(double)");

    double sum = 0;
    for(InConnection* conn : *previous) {
        sum += conn->getIn()->result * conn->getWeight();
    }

    compute(sum);
}

void Neuron::compute(double input) {
    this->input = input;
    result = activation->f(input);
}
