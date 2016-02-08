#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuronlayer.h"

class NeuralNetwork
{
public:

    // --- CONSTRUCTION ---

    NeuralNetwork();
    void CreateNetwork();


    // --- GETTERS ---

    //gets the weights from the NN
    std::vector<double> getWeights() const;

    //returns the total number of weights in the net
    int getWeightsNum() const;

    //returns the number of inputs
    int getInputsNum() const { return m_inputsNum; }

    //returns a const reference to layers
    const std::vector<NeuronLayer>& getLayers() const { return m_layers; }


    //replaces the weights with new ones
    void putWeights(std::vector<double> &weights);

    //calculates the outputs from a set of inputs
    std::vector<double> update(std::vector<double> &inputs);

    //sigmoid response curve
    double Sigmoid(double activation, double response){return 1;}

private:
    unsigned int m_inputsNum;
    unsigned int m_outputsNum;
    unsigned int m_hiddenLayersNum;
    unsigned int m_neuronsPerHiddenLayerNum;

    //storage for each layer of neurons including the output layer
    std::vector<NeuronLayer> m_layers;
};

#endif // NEURALNETWORK_H
