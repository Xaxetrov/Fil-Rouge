#include "SaveManager.h"

#include "Water.h"
#include "Meat.h"
#include "Vegetal.h"
#include "Animal.h"
#include "Carnivore.h"
#include "Herbivore.h"

#include <memory>
#include <QFile>
#include <QtXml>
#include <iostream>
#include <QString>
#include <iostream>

SaveManager::SaveManager()
{
}

int SaveManager::SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName)
{
    QString fileXmlName = neuralNetworkName;   //savePath+neuralNetworkName+".xml";
    QFile fileXml(fileXmlName);
    // Ouverture du fichier en Ã©criture et en texte. (sort de la fonction si le fichier ne s'ouvre pas)
    if(!fileXml.open(QFile::WriteOnly | QFile::Text))
    {   return false;
    }
    QXmlStreamWriter writer(&fileXml);


    // Active l'indentation automatique du fichier XML pour une meilleur visibilite
    writer.setAutoFormatting(true);

    // Insert la norme de codification du fichier XML :
    writer.writeStartDocument();

    SaveNetwork(nn,writer);

    writer.writeEndDocument();

    fileXml.close();


    return 0;
}

int SaveManager::SaveNetwork(const NeuralNetwork& nn, QXmlStreamWriter & writer)
{
    writer.writeStartElement("NeuralNetwork");

    // recuperation de quelqes informations sur le réseau de neurones
    const std::vector<NeuronLayer> layers = nn.getLayers();
    const unsigned int workingLayersNum=layers.size(); //nombre de couches cachées (en plus de l'input et de l'output)
    const unsigned int inputNum = nn.getInputNum(); // nombre d'inputs

    writer.writeStartElement("NeuronLayer");
    writer.writeAttribute("id",QString::number(0)); // 0 means "input layer"
    writer.writeTextElement("inputsNum", QString::number(inputNum));
    writer.writeEndElement();

    //for each layer
    for (unsigned int layer=1; layer<=workingLayersNum; layer++)
    {
        const std::vector<Neuron> neurons = layers.at(layer-1).getNeurons();
        unsigned int neuronsNum = neurons.size();
        writer.writeStartElement("NeuronLayer");
        writer.writeAttribute("id", QString::number(layer));

        //for each neuron
        for (unsigned int neuron=0; neuron<neuronsNum; neuron++)
        {
            writer.writeStartElement("Neuron");
            writer.writeAttribute("id",QString::number(neuron));
            const std::vector<double> weights = neurons.at(neuron).getWeights();
            if(weights.size()!=0)
            {
                QString tempS = QString::number(weights.at(0)) + " ";
                //for each weight
                for(unsigned int w=1; w<weights.size(); w++)
                {
                    tempS +=QString::number(weights.at(w)) + " " ;
                }
                writer.writeTextElement("weights", tempS);
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
    }
    writer.writeEndElement();//NeuraleNetwork
}

void SaveManager::saveWorld(const World& world, QString savingPath)
{
    QFile fileXml(savingPath);
    // Ouverture du fichier en Ã©criture et en texte. (sort de la fonction si le fichier ne s'ouvre pas)
    if(!fileXml.open(QFile::WriteOnly | QFile::Text))
    {   std::cerr << "failed to open file: " << savingPath.toStdString() << std::endl;
        return;
    }
    QXmlStreamWriter writer(&fileXml);

    // Active l'indentation automatique du fichier XML pour une meilleur visibilite
    writer.setAutoFormatting(true);

    // Insert la norme de codification du fichier XML :
    writer.writeStartDocument();

    writer.writeStartElement("World");

    writer.writeTextElement("x", QString::number(world.getSizeX()));
    writer.writeTextElement("y", QString::number(world.getSizeY()));
    writer.writeTextElement("age", QString::number(world.getWorldAge()));

    for(auto entity:world.getCopyOfEntities())
    {
        if(auto r = dynamic_pointer_cast<Resource>(entity))
        {
            saveResource(r,writer);
        }
        else if(auto a = dynamic_pointer_cast<Animal>(entity))
        {
            saveAnimal(a,writer);
        }
    }

    writer.writeEndElement();//World

    writer.writeEndDocument();

    fileXml.close();
}

void SaveManager::saveAnimal(const shared_ptr<Animal> animal, QXmlStreamWriter &writer)
{
    QString type;
    switch (animal->getTypeId()) {
    case ID_HERBIVORE:
        type = "Herbivore";
        break;
    case ID_CARNIVORE:
        type = "Carnivore";
        break;
    default:
        std::cerr << "can't save non Carnivore/Herbivore animals !" << std::endl;
        return;
    }
    writer.writeStartElement("Entity");
    writer.writeAttribute("type",type);

    writer.writeTextElement("x", QString::number(animal->getCoordinate().getX()));
    writer.writeTextElement("y", QString::number(animal->getCoordinate().getY()));
    writer.writeTextElement("radius", QString::number(animal->getRadius()));
    writer.writeTextElement("angle", QString::number(animal->getAngle()));
    writer.writeTextElement("maxSpeed", QString::number(animal->getMaxSpeed()));
    writer.writeTextElement("attack", QString::number(animal->getDamage()));
    writer.writeTextElement("energy", QString::number(animal->getEnergy()));
    writer.writeTextElement("sex", animal->isFemale()?"true":"false" );
    writer.writeTextElement("mating", QString::number(animal->getMating()));
    writer.writeTextElement("age", QString::number(animal->getAge()));
    writer.writeTextElement("hunger", QString::number(animal->getHunger()));
    writer.writeTextElement("thirst", QString::number(animal->getThirst()));
    writer.writeTextElement("health", QString::number(animal->getHealth()));

    SaveNetwork(*(animal->getBrain()),writer);

    writer.writeEndElement();//Entity
}

void SaveManager::saveResource(const shared_ptr<Resource> resource, QXmlStreamWriter &writer)
{
    QString type;
    switch (resource->getTypeId()) {
    case ID_MEAT:
        type = "Meat";
        break;
    case ID_WATER:
        type = "Water";
        break;
    case ID_VEGETAL:
        type = "Vegetal";
        break;
    default:
        std::cerr << "can't save non Meat/Water/Vegetal resources !" << std::endl;
        return;
    }
    writer.writeStartElement("Entity");
    writer.writeAttribute("type",type);

    writer.writeTextElement("x", QString::number(resource->getCoordinate().getX()));
    writer.writeTextElement("y", QString::number(resource->getCoordinate().getY()));
    writer.writeTextElement("radius", QString::number(resource->getRadius()));
    writer.writeTextElement("quantity", QString::number(resource->getQuantity()));
    writer.writeTextElement("maxQuantity", QString::number(resource->getMaxQuantity()));

    writer.writeEndElement();//Entity
}

NeuralNetwork* SaveManager::LoadNetwork(QString neuralNetworkName)
{
    const QString fileXmlName = neuralNetworkName; //savePath+neuralNetworkName+".xml"; NE FONCTIONNE PAS CHEZ MOI
    QFile* xmlFile = new QFile(fileXmlName);
    if (!xmlFile->exists())
    {   std::cout << "file does not exist" << std::endl;
        return nullptr;
    }
    else if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {   std::cout << "Can't open the file" << std::endl;
        return nullptr;
    }
    QXmlStreamReader reader(xmlFile);

    while (!reader.atEnd())
    {   QXmlStreamReader::TokenType token = reader.readNext();
        if (token==QXmlStreamReader::StartDocument)
        {   continue;
        }

        if (token==QXmlStreamReader::StartElement)
        {   if (reader.name()=="NeuralNetwork")
            {   return LoadNetwork(reader);
            }
        }
    }

    if (reader.hasError())
    {   std::cout << "Error in reading XML" << std::endl;
    }

    return nullptr;
}

NeuralNetwork* SaveManager::LoadNetwork(QXmlStreamReader & reader)
{
    std::vector<std::vector<std::vector<double> > > neuronWeights;
    int inputsNum;
    //read the neural network
    inputsNum=this->parseNeuralNetwork(reader,neuronWeights);
    //create a neural network
    NeuralNetwork * n = new NeuralNetwork(inputsNum,neuronWeights);
    return n;
}

int SaveManager::parseNeuralNetwork(QXmlStreamReader& reader, std::vector<std::vector<std::vector<double> > > &neuronWeights)
{   QString weights;
    QXmlStreamAttributes attributes;
    int inputsNum;

    if (reader.tokenType() != QXmlStreamReader::StartElement || reader.name() != "NeuralNetwork")
    {   std::cout << "Error in reading NeuralNetwork" << std::endl;
    }
    reader.readNext();
    reader.readNext();
    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "NeuralNetwork"))
    {   attributes = reader.attributes();
        // Input layer management
        if (reader.name() == "NeuronLayer" && attributes.hasAttribute("id") && attributes.value("id").toString() == "0")
        {   reader.readNext();
            reader.readNext();
            inputsNum=reader.readElementText().toInt();
            reader.readNext();
            reader.readNext();
            reader.readNext();
            reader.readNext();
        } else if (reader.name() == "NeuronLayer" && attributes.hasAttribute("id"))

        // General layer management
        {   std::vector<std::vector<double> > neuronsArray;
            reader.readNext();
            reader.readNext();
            while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "NeuronLayer"))
            {   attributes = reader.attributes();
                if (reader.name() == "Neuron" && attributes.hasAttribute("id"))

                // Neuron management
                {   std::vector<double> weightsArray;
                    reader.readNext();
                    reader.readNext();
                    if (reader.name() == "weights")
                    {   weights=reader.readElementText();
                        parseWeights(weights,weightsArray);
                    } else
                    // error
                    {   std::cout << "Error during the loading (Neuron management)" << std::endl;
                    }
                    neuronsArray.push_back(weightsArray);
                    reader.readNext();
                    reader.readNext();
                    reader.readNext();
                    reader.readNext();

                } else
                // error
                {   std::cout << "Error during the loading (General layer management)" << std::endl;
                }
            }
            neuronWeights.push_back(neuronsArray);
            reader.readNext();
            reader.readNext();

        } else
        // error
        {   std::cout << "Error during the loading" << std::endl;
        }
    }
    return inputsNum;
}

void SaveManager::parseWeights (QString weights, std::vector<double> &weightsArray)
{   QString oneWeight="";
    int i=0;
    while (i<weights.size())
    {   if (weights[i]!=' ')
        {   oneWeight+=weights[i];
        } else
        {   weightsArray.push_back(oneWeight.toDouble());
            oneWeight="";
        }
        i++;
    }
}
