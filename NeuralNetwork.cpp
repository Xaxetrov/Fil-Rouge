#include "NeuralNetwork.h"
#include "config/config.h"
#include <cstdlib>
#include <ctime>
using namespace std;

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> layerSizes)
{
    if (layerSizes.size()!=0)
    {
        m_inputsNum=layerSizes.at(0);
    }
    if (layerSizes.size()>1)
    {
        m_outputsNum = layerSizes.at(layerSizes.size()-1);
        m_hiddenLayersNum = layerSizes.size()-2;
        for(unsigned int i=1; i<layerSizes.size(); i++)
        {
            NeuronLayer nL(layerSizes.at(i), layerSizes.at(i-1));
            m_layers.push_back(nL);
        }
    }
}

NeuralNetwork::NeuralNetwork(int inputsNum, const std::vector<std::vector<std::vector<double> > > &neuronWeights) :
    m_inputsNum(inputsNum), m_outputsNum(neuronWeights.at(neuronWeights.size()-1).size()), m_hiddenLayersNum(neuronWeights.size())
{
    for(unsigned int i=0; i<neuronWeights.size(); i++)
    {
        m_layers.push_back(neuronWeights.at(i));
    }
}

vector<double> NeuralNetwork::run(std::vector<double> &inputs)
{
    vector<double> outputs; //stores the resultant outputs from each layer

    #ifdef DISABLE_NEURAL_NETWORK

    bool percepted = false;
    for(unsigned int i = 0; i < inputs.size(); i++)
    {
      if(inputs[i] > 0 && inputs[i]<40.0)
      {
        percepted = true;
        break;
      }
    }
    if(percepted)
    {
      outputs.push_back(0); // move speed 0%

      srand(std::time(0));
      int random_direction = (rand() % 2) * 2 - 1;
      outputs.push_back(random_direction * PI /*/ 2.0*/);
    }
    else
    {
      outputs.push_back(5.0); // move speed 5%
      outputs.push_back(0);
    }

    #else
        //first check that we have the correct amount of inputs
        if (inputs.size() != m_inputNum)
        {
            //just return an empty vector if incorrect.
            return outputs;
        }

        //For each layer...
        for (int computingLayer=0; computingLayer<m_hiddenLayerNum + 1; i++)
        {
            outputs.clear();

            outputs = m_layers[computingLayer].run(inputs);
            inputs = outputs;
        }
    #endif

    return outputs;
}

void NeuralNetwork::improve(int score)
{
    std::cerr << "improve method does nothing " << score << std::endl;
}
