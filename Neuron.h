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
    std::vector<double> getLastInputs() const { return m_lastInputs; }
    double getLastOutput() const { return m_lastOutput; }
    void setWeights(std::vector<double> weights) {m_weights = weights;}

    void randomise();

    double run(std::vector<double> inputs);

    void printNeuron() const;

private:
    int m_inputNum;
    std::vector<double> m_weights;
    double m_lastOutput;
    std::vector<double> m_lastInputs;

    //sigmoid response curve
    //double Sigmoid(double x){return 1/(1+exp(-x));}
    double Sigmoid(const double &x);
    //Random generator
    double RandomWeight();
};





#endif // NEURON_H
