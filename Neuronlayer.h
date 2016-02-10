#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Neuron.h"

class NeuronLayer
{
public:
    NeuronLayer(int neuronNum, int inputsPerNeuronNum);
    int getNeuronNum() const{return m_neuronNum;}
    std::vector<Neuron> getNeurons() const{return m_neurons;}
private :
    int m_neuronNum;
    std::vector<Neuron> m_neurons;
};

#endif // NEURONLAYER_H
