#include <iostream>
#include <iomanip>
#include "Neunet.h"
#include "mentors/backprop/BackpropMentor.h"

using namespace std;

void testFunction(ActivationFunction* function);

int main() {

    vector<int> layers{};

    layers.push_back(2);
    layers.push_back(2);
    layers.push_back(1);

    Neunet net(layers, new SigmoidFunction(), true);

    net.print();

    BackpropMentor mentor(&net, new MseFunction(), 0.7, 0.01);

    vector<vector<double>*>* input = new vector<vector<double>*>();
    input->push_back(new vector<double>{0.0, 0.0});
    input->push_back(new vector<double>{0.0, 1.0});
    input->push_back(new vector<double>{1.0, 0.0});
    input->push_back(new vector<double>{1.0, 1.0});

    vector<vector<double>*>* expected = new vector<vector<double>*>();
    expected->push_back(new vector<double>{0.0});
    expected->push_back(new vector<double>{1.0});
    expected->push_back(new vector<double>{1.0});
    expected->push_back(new vector<double>{0.0});

    TrainingEpoch epoch(input, expected);

    mentor.learnEpoch(epoch, 0.001);

    net.print();

    for (int iteration = 0; iteration < epoch.getIterations(); iteration++) {

        vector<double> inputTest;
        vector<double> expectedTest;

        epoch.getIteration(iteration, inputTest, expectedTest);

        vector<double>* result = net.compute(inputTest);

        cout << "( " << inputTest[0] << ", " << inputTest[1] << " ) -> " << (*result)[0] << " [ " << expectedTest[0] << " expectedTest ]" << endl;
    }

    return 0;
}

void testFunction(ActivationFunction *function) {

    double from = -10.0, to = 10.0;

    double delta = 0.1;

    for (double x = from; x < to || abs(x-to) < ActivationFunction::EPS; x += delta) {
        cout << setw(12) << right << x << " -> " << setw(12) << left << function->f(x);
        cout << "  derivative -> " << function->derivative(x) << endl;
    }
}