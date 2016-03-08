#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <iostream>
#include <cmath>

class Neuron
{
public:
    Neuron(int inputNum);
    Neuron(const std::vector<double>& weights);

    int getInputsNum() {return m_inputNum;}
    std::vector<double> getWeights() const{return m_weights;}

     double run(std::vector<double> inputs);

private:
    int m_inputNum;
    std::vector<double> m_weights;

    //sigmoid response curve
    double Sigmoid(double x){return 1/(1+exp(-x));}
    //Random generator
    double RandomWeight();
};

#endif // NEURON_H
