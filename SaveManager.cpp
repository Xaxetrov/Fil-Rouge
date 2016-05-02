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
        if(auto r = std::dynamic_pointer_cast<Resource>(entity))
        {
            saveResource(r,writer);
        }
        else if(auto a = std::dynamic_pointer_cast<Animal>(entity))
        {
            saveAnimal(a,writer);
        }
    }

    writer.writeEndElement();//World

    writer.writeEndDocument();

    fileXml.close();
}

void SaveManager::saveAnimal(const std::shared_ptr<Animal> animal, QXmlStreamWriter &writer)
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

void SaveManager::saveResource(const std::shared_ptr<Resource> resource, QXmlStreamWriter &writer)
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

World SaveManager::loadWorld(QString savingPath)
{
    World world;
    QFile* xmlFile = new QFile(savingPath);
    if(!xmlFile->exists())
    {
      std::cout << "file does not exist" << std::endl;
    }

    if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    { //error
      std::cout << "Can't open the file" << std::endl;
    }
    QXmlStreamReader reader(xmlFile);

    while(!reader.atEnd() && !reader.hasError())
    {
      QXmlStreamReader::TokenType token = reader.readNext();
      if(token == QXmlStreamReader::StartDocument)
      { continue;
      }

      if(token == QXmlStreamReader::StartElement)
      {
       if(reader.name() == "World")
       {
          this->parseWorld(world, reader);
       }
      }
    }
    if(reader.hasError())
    { std::cout << "Error in reading XML in constructor" << std::endl;
    }
    delete xmlFile;
    return world;
}

void SaveManager::parseWorld(World& world, QXmlStreamReader& reader)
{
  int xWorld, yWorld;
  unsigned ageWorld;

  if(reader.tokenType() != QXmlStreamReader::StartElement &&
     reader.name() != "World")
  { // error
    std::cout << "Error in reading Wolrd" << std::endl;
  }
  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "World"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "Entity")
      {
        this->parseEntity(world, reader);
      }
      else if(reader.name() == "x")
      {
        xWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "y")
      {
        yWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "age")
      {
        ageWorld = reader.readElementText().toUInt();
      }
      else
      { //error
        std::cout << "Unknown Token" << std::endl;
      }
    }
    reader.readNext();
  }
  world.setSize(xWorld,yWorld);
  world.setWorldAge(ageWorld);
}

void SaveManager::parseEntity(World& world, QXmlStreamReader& reader)
{
  QString type;
  double xEntity=0.0, yEntity=0.0, radiusEntity=INITIAL_RADIUS;
  double angle = 0.0;
  int maxSpeed = MAX_SPEED;
  double attack = -2;
  double energy = DEFAULT_ENERGY;
  bool sex = true;
  NeuralNetwork * nn = nullptr;
  int mating = 0;
  int age = 0;
  int quantity = 0, maxQuantity = 0;
  int hunger = 0;
  int thirst = 0;
  int health = MAX_HEALTH;

  if(!reader.tokenType() == QXmlStreamReader::StartElement &&
      reader.name() == "Entity")
  { //error
  }

  QXmlStreamAttributes attributes = reader.attributes();
  if(attributes.hasAttribute("type"))
  {
    type = attributes.value("type").toString();
  }
  else
  { //error
    std::cout << "No Attribute type" << std::endl;
  }

  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "Entity"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "x")
      {
          xEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "y")
      {
          yEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "radius")
      {
          radiusEntity = reader.readElementText().toDouble();
      }
      else if(reader.name() == "angle")
      {
          angle = reader.readElementText().toDouble();
      }
      else if(reader.name() == "attack")
      {
          attack = reader.readElementText().toDouble();
      }
      else if(reader.name() == "energy")
      {
          energy = reader.readElementText().toDouble();
      }
      else if(reader.name() == "sex")
      {
          sex = (reader.readElementText().toLower()=="true");
      }
      else if(reader.name() == "maxSpeed")
      {
          maxSpeed = reader.readElementText().toInt();
      }
      else if(reader.name() == "NeuralNetwork")
      {
          SaveManager savManager;
          nn = savManager.LoadNetwork(reader);
      }
      else if(reader.name() == "mating")
      {
          mating = reader.readElementText().toInt();
      }
      else if(reader.name() == "age")
      {
          age = reader.readElementText().toInt();
      }
      else if(reader.name() == "quantity")
      {
          quantity = reader.readElementText().toInt();
      }
      else if(reader.name() == "maxQuantity")
      {
          maxQuantity = reader.readElementText().toInt();
      }
      else if(reader.name() == "hunger")
      {
          hunger = reader.readElementText().toInt();
      }
      else if(reader.name() == "thirst")
      {
          thirst = reader.readElementText().toInt();
      }
      else if(reader.name() == "health")
      {
          health = reader.readElementText().toInt();
      }
      else
      { //error
      }
    }
    reader.readNext();
  }

  if(type == "Vegetal")
  {
    if(maxQuantity==0)
        maxQuantity=VEGETAL_MAXQUANTITY;
    if(quantity==0)
        quantity=maxQuantity;
    std::shared_ptr<Vegetal> entity( std::make_shared<Vegetal>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Water")
  {
      if(maxQuantity==0)
          maxQuantity=WATER_MAXQUANTITY;
      if(quantity==0)
          quantity=maxQuantity;
    std::shared_ptr<Water> entity( std::make_shared<Water>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Meat")
  {
    std::shared_ptr<Meat> entity( std::make_shared<Meat>(xEntity, yEntity, radiusEntity, maxQuantity));
    entity->setCurrantQuantity(quantity);
    world.addEntity(entity);
  }
  else if(type == "Herbivore")
  {
      if(nn == nullptr)
      {
          std::vector<unsigned int> layerSizes;
          for(unsigned int i = 0; i < NB_LAYERS; i++)
          {
            layerSizes.push_back(LAYER_SIZES[i]);
          }
          nn = new NeuralNetwork(layerSizes);
      }
      if(attack==-2)
          attack = ATTACK_HERBIVORE;
      std::shared_ptr<Herbivore> entity( std::make_shared<Herbivore>(xEntity, yEntity, radiusEntity,maxSpeed, attack, energy, &world, nn, mating));
      entity->setSex(sex);
      entity->setAge(age);
      entity->setAngle(angle);
      entity->setHunger(hunger);
      entity->setThirst(thirst);
      entity->setHealth(health);
      world.addEntity(entity);
  }
  else if(type == "Carnivore")
  {
      if(nn == nullptr)
      {
          std::vector<unsigned int> layerSizes;
          for(unsigned int i = 0; i < NB_LAYERS; i++)
          {
            layerSizes.push_back(LAYER_SIZES[i]);
          }
          nn = new NeuralNetwork(layerSizes);
      }
      if(attack==-2)
          attack = ATTACK_CARNIVORE;
      std::shared_ptr<Carnivore> entity( std::make_shared<Carnivore>(xEntity, yEntity, radiusEntity,maxSpeed, attack, energy, &world, nn, mating));
      entity->setSex(sex);
      entity->setAge(age);
      entity->setAngle(angle);
      entity->setHunger(hunger);
      entity->setThirst(thirst);
      entity->setHealth(health);
      world.addEntity(entity);
  }


}
