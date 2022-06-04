#pragma once
#include <iostream>
#include <vector>

using namespace std;

class TrainingEpoch {

public:

    TrainingEpoch(vector<vector<double>*>* input, vector<vector<double>*>* expected): input(input), expected(expected) { }
    ~TrainingEpoch() {
        for(auto v : *input)
            delete v;
        for(auto v : *expected)
            delete v;
        delete input, expected;
    }

    int getIterations() { return input->size(); }

    void getIteration(int index, vector<double>& outInput, vector<double>& outExpected) {
        outInput = *(*input)[index];
        outExpected = *(*expected)[index];
    }

    vector<vector<double>*>* getInput() { return input; }
    vector<vector<double>*>* getExpected() { return expected; }

private:
    vector<vector<double>*>* input;
    vector<vector<double>*>* expected;
};