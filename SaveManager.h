#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "NeuralNetwork.h"
#include "World.h"
#include "Animal.h"
#include "Resource.h"
#include <memory>
#include <QString>
#include <QtXml>

static const QString savePath("../save/");

class SaveManager
{
public:
    SaveManager();
    int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    int SaveNetwork(const NeuralNetwork& nn, QXmlStreamWriter & writer);
    void saveWorld(const World& world, QString savingPath);
    void saveAnimal(const std::shared_ptr<Animal> animal, QXmlStreamWriter & writer);
    void saveResource(const std::shared_ptr<Resource> resource, QXmlStreamWriter & writer);

    World loadWorld(QString savingPath);
    void parseWorld(World& world, QXmlStreamReader& reader);
    void parseEntity(World& world, QXmlStreamReader& reader);

    NeuralNetwork *LoadNetwork(QString neuralNetworkName="temp");
    NeuralNetwork *LoadNetwork(QXmlStreamReader& reader);
    int parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights);
    void parseWeights(QString weights, std::vector<double> &weightsArray);
};

#endif // SAVEMANAGER_H
