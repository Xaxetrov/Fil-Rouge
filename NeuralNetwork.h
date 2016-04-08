//#define DISABLE_NEURAL_NETWORK // Disables the neural network and uses instead a simple AI to test the world and the perception.

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuronlayer.h"

class NeuralNetwork
{
public:

    // --- CONSTRUCTION ---

    NeuralNetwork(std::vector<unsigned int> layerSizes); // sending [3,5,2] means 3 input neurons, 5 hiddens and 2 outputs with equal weights
    NeuralNetwork(int inputsNum,const std::vector<std::vector<std::vector<double>>>& neuronWeights);
    NeuralNetwork(const NeuralNetwork& father, const NeuralNetwork& mother);

    // --- GETTERS ---

    //gets the weights from the NN
    std::vector<double> getWeights() const;

    //returns the total number of weights in the net
    int getWeightNum() const;
    //returns the number of inputs
    int getInputNum() const { return m_inputNum; }
    //returns the number of outputs
    int getOutputNum() const { return m_outputNum; }
    //returns the number of hidden layers
    int getHiddenLayerNum() const { return m_hiddenLayerNum; }

    //returns a const reference to layers
    const std::vector<NeuronLayer>& getLayers() const { return m_layers; }


    //replaces the weights with new ones
    void putWeights(std::vector<double> &weights);

    //calculates the outputs from a set of inputs
    std::vector<double> run(std::vector<double> &inputs);

    //ajust the weights to improve the performance of the network
    //score : number (positive/negative) that caracterizes the results of the last network uses.
    void improve(int score);

    //print in the console all the neurons -> for debugging
    void printNetwork() const;

private:
    unsigned int m_inputNum;
    unsigned int m_outputNum;
    unsigned int m_hiddenLayerNum;

    //storage for each layer of neurons including the output layer
    std::vector<NeuronLayer> m_layers;
};

#endif // NEURALNETWORK_H
