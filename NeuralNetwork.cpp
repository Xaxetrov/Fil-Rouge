#include "NeuralNetwork.h"

using namespace std;

NeuralNetwork::NeuralNetwork()
{

}

vector<double> NeuralNetwork::update(std::vector<double> &inputs)
{
    vector<double> outputs; //stores the resultant outputs from each layer
    int weight = 0;

    //first check that we have the correct amount of inputs
    if (inputs.size() != m_inputNum)
    {
        //just return an empty vector if incorrect.
        return outputs;
    }

    //For each layer...
    for (int i=0; i<m_hiddenLayerNum + 1; ++i)
    {
        if ( i > 0 )
        {
            inputs = outputs;
        }
        outputs.clear();
        weight = 0;

        //for each neuron sum the (inputs * corresponding weights).Throw
        //the total at our sigmoid function to get the output.
        for (int j=0; j<m_layers[i].getNeuronNum(); ++j)
        {
            double netInput = 0;
            int inputsNum = m_layers[i].getNeurons()[j].getInputsNum();

            //for each weight
            for (int k=0; k<inputsNum - 1; ++k)
            {
                //sum the weights * inputs
                netInput += m_layers[i].getNeurons()[j].getWeights()[k] * inputs[weight++];
            }

            //add in the bias
            netInput += m_layers[i].getNeurons()[j].getWeights()[inputsNum-1] * -1/*CParams::dBias*/;

            //we can store the outputs from each layer as we generate them.
            //The combined activation is first filtered through the sigmoid function
            outputs.push_back(Sigmoid(netInput, 0.7/*CParams::dActivationResponse*/));

            weight = 0;
        }
    }

    return outputs;
}