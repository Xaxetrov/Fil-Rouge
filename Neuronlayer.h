#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Neuron.h"

class NeuronLayer
{
public:
    NeuronLayer(int neuronNum, int inputsPerNeuronNum);

private :
    int m_neuronNum;
    std::vector<Neuron> m_neurons;
};

#endif // NEURONLAYER_H
