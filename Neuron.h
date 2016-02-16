#ifndef NEURON_H
#define NEURON_H

#include <stdlib.h>

#include <vector>


class Neuron
{
public:
    Neuron(int inputNum);
    Neuron(const std::vector<double>& weights);
    double RandomWeight();
    int getInputsNum() {return m_inputNum;}
    std::vector<double> getWeights() const{return m_weights;}

private:
    int m_inputNum;
    std::vector<double> m_weights;
};

#endif // NEURON_H
