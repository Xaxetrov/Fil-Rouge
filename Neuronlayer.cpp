#include "Neuronlayer.h"


NeuronLayer::NeuronLayer(int neuronNum, int inputsPerNeuronNum) :
    m_neuronNum(neuronNum)
{
    for(int i=0; i<m_neuronNum; i++)
    {
        m_neurons.push_back(inputsPerNeuronNum);
    }
}

NeuronLayer::NeuronLayer(const std::vector<std::vector<double>>& neuronWeights) : m_neuronNum(neuronWeights.size())
{
    for(unsigned int i=0; i< neuronWeights.size(); i++)
    {
        m_neurons.push_back(neuronWeights.at(i));
    }
}

NeuronLayer::NeuronLayer(const std::vector<Neuron>& neurons)
{
    m_neuronNum = neurons.size();
    m_neurons.clear();
    for(const auto & neuron : neurons)
    {
        m_neurons.push_back(neuron);
    }
}

std::vector<double> NeuronLayer::run(std::vector<double> inputs)
{
    std::vector<double> outputs;
    for(int i=0; i<m_neuronNum; i++)
    {
        outputs.push_back(m_neurons[i].run(inputs));
    }
    return outputs;
}

void NeuronLayer::printLayer() const
{
    for(unsigned int i = 0; i < m_neurons.size(); i++)
    {
        std::cout << "Neuron " << i << " : ";
        m_neurons[i].printNeuron();
        std::cout << std::endl;
    }
}
