#include "Neuronlayer.h"


NeuronLayer::NeuronLayer(int neuronNum, int inputsPerNeuronNum) :
    m_neuronNum(neuronNum)
{
    for(int i=0; i<m_neuronNum; i++)
    {
        m_neurons.push_back(inputsPerNeuronNum);
    }
}

