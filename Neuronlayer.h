#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Neuron.h"

class NeuronLayer
{
public:
    NeuronLayer(int neuronNum, int inputsPerNeuronNum);
    NeuronLayer(const std::vector<std::vector<double>>& neuronWeights);
    NeuronLayer(const std::vector<Neuron>& neurons);

    int getNeuronNum() const{return m_neuronNum;}
    std::vector<Neuron> getNeurons() const{return m_neurons;}

    std::vector<double> run(std::vector<double> inputs);
private :
    int m_neuronNum;
    std::vector<Neuron> m_neurons;
};

#endif // NEURONLAYER_H
