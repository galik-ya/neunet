#include <iostream>
#include "../Neunet.h"
#include "../Exception.hpp"
#include "../functions/BiasFunction.hpp"

Neunet::Neunet(const vector<int>& layersNum, ActivationFunction* activation, bool bias): activation(activation), bias(bias) {

    srand((time(nullptr) * 7) / 3); // Some random

    if(layersNum.size() < 2)
        throw Exception("Number of layersNum < 2");

    vector<Neuron*>* lastLayer = nullptr;

   layers = new vector<vector<Neuron*>*>();

    for (int i = 0; i < layersNum.size(); i++) {
        int number = layersNum[i];

        auto layer = new vector<Neuron*>();

        for (int i = 0; i < number; i++) {
            Neuron* neuron;

            if(lastLayer != nullptr)
                neuron = new Neuron(activation, lastLayer);
            else
                neuron = new Neuron(activation);

            layer->push_back(neuron);
        }

        if(bias && i != layersNum.size()-1)
            layer->push_back(new Neuron(new BiasFunction()));

        lastLayer = layer;

        layers->push_back(layer);
    }
}

Neunet::~Neunet() {
    vector<Neuron*>* inputLayer = (*layers)[0];
    for (int i = 0; i < inputLayer->size(); i++)
        (*inputLayer)[i]->deleteForward(i == 0);
    delete inputLayer;

    delete layers, activation;
}

vector<double>* Neunet::compute(vector<double>& input) {

    auto result = new vector<double>;

    for (int i = 0; i < layers->size(); i++) {
        vector<Neuron*>* layer = (*layers)[i];
        for(int j = 0; j < layer->size(); j++){
            Neuron* neuron = (*layer)[j];

            if(i == 0)
                neuron->compute(input[j]);
            else
                neuron->compute();

            if(i == layers->size()-1)
                result->push_back(neuron->getResult());
        }
    }

    return result;
}

void Neunet::print() {
    for (int i = 0; i < layers->size(); i++) {
        vector<Neuron*>* layer = (*layers)[i];
        cout << "Layer " << i << endl;
        for (int j = 0; j < layer->size(); j++) {
            Neuron* neuron = (*layer)[j];
            cout << "\tNeuron " << neuron << " ( " << neuron->getInput() << " ) -> " << neuron->getResult() << endl;
            if(neuron->getOutConnections() == nullptr)
                continue;
            for (auto conn : *neuron->getOutConnections()) {
                cout << "\t\tConnection to " << conn->getOut() << " with weight " << conn->getWeight() << endl;
            }
            cout << endl;
        }
    }
}
