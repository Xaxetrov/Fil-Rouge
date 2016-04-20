#include "Neuron.h"
#include <random>
#include <algorithm>
#include <iomanip>

Neuron::Neuron(int inputNum) : m_inputNum(inputNum)
{
    //we need an additional weight for the bias hence the +1
    for (int i=0; i<inputNum + 1; i++)
    {
        //set up the weights with an initial random value
        m_weights.push_back(RandomWeight());
    }
}

Neuron::Neuron(const std::vector<double>& weights) : m_inputNum(weights.size()), m_weights(weights)
{
    /*for(unsigned int i=0; i<weights.size(); i++)
    {
        m_weights.push_back(weights.at(i));
    }*/
}

double Neuron::run(std::vector<double> inputs)
{
    double sum = 0;
    int inputSize = inputs.size();
    int weightsSize = m_weights.size()-1;
    //bad size of inputs
    if(inputs.size() != m_weights.size()-1)
    {
        return 0;
    }
    //sums the weights * inputs
    for(unsigned int i=0; i<m_weights.size()-1; i++)
    {
        sum += m_weights[i] * inputs[i];
    }
    //adds in the bias
    sum += m_weights[m_weights.size()-1];
    //goes through the sigmoid and returns;
    return Sigmoid(sum);
}

double  Neuron::RandomWeight()
{
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(0, 1);
    return distribution(generator);
}

void Neuron::printNeuron() const
{
    for(unsigned int i = 0; i < m_weights.size(); i++)
    {
        std::cout << m_weights[i] << " ";
    }
}
