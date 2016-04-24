#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include "config/config.h"

class Neuron
{
public:
    Neuron(int inputNum);
    Neuron(const std::vector<double>& weights);

    int getInputsNum() {return m_inputNum;}
    std::vector<double> getWeights() const{return m_weights;}
    std::vector<double>* getPointerToWeights() {return &m_weights;}
    void setWeights(std::vector<double> weights) {m_weights = weights;}

    double run(std::vector<double> inputs);

    void printNeuron() const;

private:
    int m_inputNum;
    std::vector<double> m_weights;

    //sigmoid response curve
    //double Sigmoid(double x){return 1/(1+exp(-x));}
    double Sigmoid(double x){return atan(x)*(2/PI);} //to get negative number in [-1,1]
    //Random generator
    double RandomWeight();
};





#endif // NEURON_H
