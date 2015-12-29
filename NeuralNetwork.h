#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuronlayer.h"

class NeuralNetwork
{
public:
    NeuralNetwork();
    void CreateNetwork();

    //gets the weights from the NN
    std::vector<double> getWeights() const;

    //returns the total number of weights in the net
    int getWeightsNum() const;

    //replaces the weights with new ones
    void putWeights(std::vector<double> &weights);

    //calculates the outputs from a set of inputs
    std::vector<double> update(std::vector<double> &inputs);

    //sigmoid response curve
    double Sigmoid(double activation, double response){return 1;}

private:
    int m_inputNum;
    int m_outputNum;
    int m_hiddenLayerNum;
    int m_neuronsPerHiddenLayerNum;

    //storage for each layer of neurons including the output layer
    std::vector<NeuronLayer> m_layers;
};

#endif // NEURALNETWORK_H
