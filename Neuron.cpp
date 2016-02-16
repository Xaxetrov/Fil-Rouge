#include "Neuron.h"

Neuron::Neuron(int inputNum) : m_inputNum(inputNum)
{

    //we need an additional weight for the bias hence the +1
    for (int i=0; i<inputNum+1; ++i)
    {
        //set up the weights with an initial random value
        m_weights.push_back(RandomWeight());
    }
}

Neuron::Neuron(const std::vector<double>& weights) : m_inputNum(weights.size())
{
    for(unsigned int i=0; i<weights.size(); i++)
    {
        m_weights.push_back(weights.at(i));
    }
}

double  Neuron::RandomWeight()
{
    double bottom = (double) rand() / (RAND_MAX) - 1;
    double top = (double) rand() / (RAND_MAX);
    return (top+bottom);
}

