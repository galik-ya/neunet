#pragma once

#include <iostream>

class Neuron;

class Connection {
public:
    virtual double getWeight() = 0;
    virtual void adjustWeight(double delta) = 0;
};

class InConnection: public Connection {
public: virtual Neuron* getIn() = 0;
};

class OutConnection: public Connection {
public: virtual Neuron* getOut() = 0;
};

class InOutConnection: public InConnection, public OutConnection {

public:
    InOutConnection(Neuron* in, Neuron* out): in(in), out(out) {
        weight = ((double)rand()) / RAND_MAX;
    }

    double getWeight() final { return weight; }

    void adjustWeight(double delta) final { weight += delta; };

    Neuron* getIn() final { return in; }

    Neuron* getOut() final { return out; }

private:
    double weight;

    Neuron* in, *out;
};