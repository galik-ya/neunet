#include <iostream>
#include "../BackpropMentor.h"

BackpropMentor::BackpropMentor(Neunet* net, ErrorFunction* error, double epsilon, double momentum)
        : net(net), error(error), epsilon(epsilon), momentum(momentum) {

}

void BackpropMentor::learnEpoch(TrainingEpoch& epoch, double beforeErrorLess) {

    int epochNum = 0;
    while(true) {
        epochNum++;

        bool learning = false;

        int avgErrorNum = 0;
        double avgError = 0.0;

        for (int iteration = 0; iteration < epoch.getIterations(); iteration++) {

            vector<double> input;
            vector<double> expected;

            epoch.getIteration(iteration, input, expected);

            vector<double> *result = net->compute(input);

            double iterationError = error->f(*result, expected);

            if(iterationError > beforeErrorLess)
                learning = true;

            avgErrorNum++;
            avgError += iterationError;

            learn(*result, expected);

            delete result;
        }

        if(epochNum % 1000 == 0 || !learning)
            cout << endl << "--------------- Epoch number " << epochNum << ", average error " << avgError / avgErrorNum << " ---------------" << endl << endl;

        if(!learning)
            break;
    }
}

void BackpropMentor::learn(vector<double>& actual, vector<double>& expected) {

    int lastLayerNum = net->getLayers()->size()-1;

    for (int layerNum = lastLayerNum; layerNum >= 0; layerNum--) {
        vector<Neuron*>* layer = (*net->getLayers())[layerNum];

        for (int neuronNum = 0; neuronNum < layer->size(); neuronNum++) {
            Neuron* neuron = (*layer)[neuronNum];

            double delta;
            if(layerNum == lastLayerNum)
                delta = firstDelta(actual[neuronNum], expected[neuronNum], neuron);
            else
                delta = hiddenDelta(neuron);

            valueMap.insert_or_assign(neuron, delta);

            if(layerNum != lastLayerNum)
                adjustWeight(neuron);
        }
    }
}

double BackpropMentor::firstDelta(double actual, double expected, Neuron *neuron) {
    return (expected - actual) * neuron->getActivation()->derivative(neuron->getInput());
}

double BackpropMentor::hiddenDelta(Neuron* neuron) {
    double sum = 0;
    for(OutConnection* conn : *neuron->getOutConnections()) {
        Neuron* out = conn->getOut();
        double outDelta = valueMap[out];
        sum += outDelta * conn->getWeight();
    }
    return sum * neuron->getActivation()->derivative(neuron->getInput());
}

void BackpropMentor::adjustWeight(Neuron* neuron) {
    for(OutConnection* conn : *neuron->getOutConnections()) {
        double grad = valueMap[conn->getOut()] * neuron->getResult();
        double oldDeltaW;
        try {
            oldDeltaW = valueMap.at(conn);
        } catch(out_of_range& e) {
            oldDeltaW = 0.0;
        }
        double deltaW = epsilon * grad + momentum * oldDeltaW;

        valueMap[conn] = deltaW;

        conn->adjustWeight(deltaW);
    }
}
