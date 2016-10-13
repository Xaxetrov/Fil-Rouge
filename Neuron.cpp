#include "Neuron.h"
#include <random>
#include <algorithm>
#include <iomanip>
#include "config/config.h"
#include <cstdlib>
#include <ctime>

#ifdef USE_INTEL_IPP
    #include <ipp.h>
    #include <ipps.h>
#endif

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
    if(inputSize != weightsSize)
    {
        return 0;
    }
    m_lastInputs = inputs;
    //sums the weights * inputs
#ifndef USE_INTEL_IPP
    for(int i=0; i< weightsSize; i++)
    {
        sum += m_weights[i] * inputs[i];
    }
#else
    Ipp64f productVector[weightsSize];
    ippsMul_64f(m_weights.data(),inputs.data(),productVector,weightsSize); // multiply input and weight into productVector
    ippsSum_64f(productVector,weightsSize,&sum); // sum product vector element
#endif
    //adds in the bias
    sum += m_weights[weightsSize];
    //goes through the sigmoid and returns;
    m_lastOutput = Sigmoid(sum);
    return m_lastOutput;
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

void Neuron::randomise()
{
    static std::mt19937 modificationGenerator(std::random_device{}());
    std::bernoulli_distribution modificationDistribution(config::NN_WEIGHT_CHANGE_PROBABILITY); // % chance to change one weight of a neurone
    static std::mt19937 randomChangeGenerator(std::random_device{}());
    std::normal_distribution<double> randomChangeDistribution(config::NN_WEIGHT_CHANGE_AVERAGE_VALUE,
                                                         config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION); // change on weight are of average 0 and standart variation 0,1 (addition)

    double weight;
    for(unsigned i=0 ; i<m_weights.size() ; i++)
    {
        if(modificationDistribution(modificationGenerator))
        {
            weight = m_weights.at(i);
            weight += randomChangeDistribution(randomChangeGenerator);
            m_weights[i] = weight;
        }
    }
}

double Neuron::Sigmoid(const double &x)
{
#ifndef USE_INTEL_IPP
    return atan(x)*(2.0/PI); //to get negative number in [-1,1]
#else
    Ipp64f ret = static_cast<Ipp64f>(x);
    ippsArctan_64f_I( &ret, 1);
    ret*=(2.0/PI);
    return static_cast<double>(ret);
#endif
}
