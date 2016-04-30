#include "SaveManager.h"

#include <QFile>
#include <QtXml>
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

    // element racine du fichier XML
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

    writer.writeEndDocument();

    fileXml.close();


    return 0;
}

NeuralNetwork* SaveManager::LoadNetwork(QString neuralNetworkName)
{
    /*std::vector<unsigned int> myV;
    myV.push_back(1);
    myV.push_back(1);
    myV.push_back(1);
    NeuralNetwork n(myV);*/


    const QString fileXmlName = neuralNetworkName; //savePath+neuralNetworkName+".xml"; NE FONCTIONNE PAS CHEZ MOI
    QFile* xmlFile = new QFile(fileXmlName);
    if (!xmlFile->exists())
    {   std::cout << "file does not exist" << std::endl;
    }
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {   std::cout << "Can't open the file" << std::endl;
    }
    QXmlStreamReader reader(xmlFile);
    std::cerr<<"file opened !"<<std::endl;/////////////////////////////////////////////////A supprimer quand debug terminé

    return LoadNetwork(reader);
}

NeuralNetwork* SaveManager::LoadNetwork(QXmlStreamReader & reader)
{
    std::vector<std::vector<std::vector<double> > > neuronWeights;
    int inputsNum;

    while (!reader.atEnd())
    {   QXmlStreamReader::TokenType token = reader.readNext();
        if (token==QXmlStreamReader::StartDocument)
        {   continue;
        }

        if (token==QXmlStreamReader::StartElement)
        {   if (reader.name()=="NeuralNetwork")
            {   inputsNum=this->parseNeuralNetwork(reader,neuronWeights);
            }
        }
    }

    if (reader.hasError())
    {   std::cout << "Error in reading XML" << std::endl;
    }

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
