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
    //Network operations
    static int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    static int SaveNetwork(const NeuralNetwork& nn, QXmlStreamWriter & writer);
    static NeuralNetwork *LoadNetwork(QString neuralNetworkName="temp");
    static NeuralNetwork *LoadNetwork(QXmlStreamReader& reader);

    //World operations
    static void saveWorld(const World& world, QString savingPath);
    static World loadWorld(QString savingPath);
    static void loadWorld(QString savingPath, World * newWorld);

    //Other operations
    static void saveAnimal(const std::shared_ptr<Animal> animal, QXmlStreamWriter & writer);
    static void saveResource(const std::shared_ptr<Resource> resource, QXmlStreamWriter & writer);

private:
    //Parsers
    static void parseWorld(World *world, QXmlStreamReader& reader);
    static void parseEntity(World *world, QXmlStreamReader& reader);
    static int parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights);
    static void parseWeights(QString weights, std::vector<double> &weightsArray);
};

#endif // SAVEMANAGER_H
