#ifndef NEURON_H
#define NEURON_H

#include <stdlib.h>

#include <vector>


class Neuron
{
public:
    Neuron(int inputNum);
    double RandomWeight();

private:
    int m_inputNum;
    std::vector<double> m_weights;
};

#endif // NEURON_H
