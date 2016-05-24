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

/*
 * The Save Manager class is designed to manage all save and load operations.
 * In particular it can write and read xml files and their object counterparts
 */
class SaveManager
{
public:
    // constructor
    SaveManager();

    //Network operations
    int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    int SaveNetwork(const NeuralNetwork& nn, QXmlStreamWriter & writer);
    NeuralNetwork *LoadNetwork(QString neuralNetworkName="temp");
    NeuralNetwork *LoadNetwork(QXmlStreamReader& reader);

    //World operations
    void saveWorld(const World& world, QString savingPath);
    World loadWorld(QString savingPath);
    void loadWorld(QString savingPath, World * newWorld);

    //Other operations
    void saveAnimal(const std::shared_ptr<Animal> animal, QXmlStreamWriter & writer);
    void saveResource(const std::shared_ptr<Resource> resource, QXmlStreamWriter & writer);

private:
    //Parsers
    void parseWorld(World *world, QXmlStreamReader& reader);
    void parseEntity(World *world, QXmlStreamReader& reader);
    int parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights);
    void parseWeights(QString weights, std::vector<double> &weightsArray);
};

#endif // SAVEMANAGER_H
