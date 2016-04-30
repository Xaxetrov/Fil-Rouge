#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "NeuralNetwork.h"
#include <QString>
#include <QtXml>

static const QString savePath("../save/");

class SaveManager
{
public:
    SaveManager();
    int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    NeuralNetwork *LoadNetwork(QString neuralNetworkName="temp");
    NeuralNetwork *LoadNetwork(QXmlStreamReader& reader);
    int parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights);
    void parseWeights(QString weights, std::vector<double> &weightsArray);
};

#endif // SAVEMANAGER_H
