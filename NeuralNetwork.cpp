#include "NeuralNetwork.h"
#include "config/config.h"
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

NeuralNetwork::NeuralNetwork(std::vector<unsigned int> layerSizes)
{
    if (layerSizes.size()!=0)
    {
        m_inputNum=layerSizes.at(0);
    }
    if (layerSizes.size()>1)
    {
        m_outputNum = layerSizes.at(layerSizes.size()-1);
        m_hiddenLayerNum = layerSizes.size()-2;
        for(unsigned int i=1; i<layerSizes.size(); i++)
        {
            NeuronLayer nL(layerSizes.at(i), layerSizes.at(i-1));
            m_layers.push_back(nL);
        }
    }
}

NeuralNetwork::NeuralNetwork(int inputsNum, const std::vector<std::vector<std::vector<double> > > &neuronWeights) :
    m_inputNum(inputsNum), m_outputNum(neuronWeights.at(neuronWeights.size()-1).size()), m_hiddenLayerNum(neuronWeights.size())
{
    for(unsigned int i=0; i<neuronWeights.size(); i++)
    {
        m_layers.push_back(neuronWeights.at(i));
    }
}

//TO FINISH
NeuralNetwork::NeuralNetwork(const NeuralNetwork& father, const NeuralNetwork& mother)
{
    //checks if sizes correspond
    if(father.getInputNum() != mother.getInputNum()
            || father.getLayers().size() != mother.getLayers().size())
    {
            cerr << "error, mother and father NN of different sizes" << endl;
    }
    for(unsigned int i=0; i<father.getLayers().size(); i++)
    {
        if (father.getLayers()[i].getNeurons().size() != mother.getLayers()[i].getNeurons().size())
        {
            cerr << "error, mother and father NN of different sizes" << endl;
        }
    }
    m_inputNum = father.getInputNum();
    m_outputNum = father.getOutputNum();
    m_hiddenLayerNum = father.getHiddenLayerNum();

    vector<Neuron> childNeurons;
    default_random_engine generator(random_device{}());
    bernoulli_distribution distribution(0.5);


    for(int i = 0; i < father.m_layers.size(); i++)
    {
        const auto& fatherLayer = father.m_layers[i];
        const auto& motherLayer = mother.m_layers[i];
        for(int j = 0; j < fatherLayer.getNeuronNum(); j++)
        {
            const auto& fatherNeurons = fatherLayer.getNeurons();
            const auto& motherNeurons = motherLayer.getNeurons();

            // 1/2 chance to take the mother neuron
            if(distribution(generator))
            {
                childNeurons.push_back(motherNeurons[j]);
            }
            else
            {
                childNeurons.push_back(fatherNeurons[i]);
            }
        }
        m_layers.push_back(childNeurons);
        childNeurons.clear();

    }
}

vector<double> NeuralNetwork::run(std::vector<double> &inputs)
{
    vector<double> outputs; //stores the resultant outputs from each layer

    #ifdef DISABLE_NEURAL_NETWORK

    bool percepted = false;
    for(unsigned int i = 0; i < inputs.size(); i++)
    {
      if(i%2 == 0 && inputs[i] == 20)
      {
        percepted = true;
        break;
      }
    }
    if(percepted)
    {
//      outputs.push_back(0); // move speed 0%
//      srand(std::time(0));
//      int random_direction = (rand() % 2) * 2 - 1;
//      outputs.push_back(random_direction * PI / 2.0);

        outputs.push_back(0); // move speed 0%
        outputs.push_back(-PI);
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
