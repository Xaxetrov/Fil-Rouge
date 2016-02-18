#include "SaveManager.h"

#include <QFile>
#include <QtXml>
#include <iostream>

SaveManager::SaveManager()
{
}

int SaveManager::SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName)
{
    QString fileXmlName = savePath+neuralNetworkName+".xml";
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
    const unsigned int inputNum = nn.getInputsNum(); // nombre d'inputs

    writer.writeStartElement("NeuronLayer");
    writer.writeAttribute("id",QString::number(0)); // 0 means "input layer"
    writer.writeTextElement("inputsNum", QString::number(inputNum));
    writer.writeComment("this is the input layer");
    writer.writeEndElement();

    //for each layer
    for (unsigned int layer=1; layer<=workingLayersNum; layer++)
    {
        const std::vector<Neuron> neurons = layers.at(layer-1).getNeurons();
        unsigned int neuronsNum = neurons.size();
        writer.writeStartElement("NeuronLayer");
        writer.writeAttribute("id", QString::number(layer));
        if(layer == workingLayersNum)
        {
            writer.writeComment("this is the output layer");
        }
        writer.writeComment("this is the output layer");
        //for each neuron
        for (unsigned int neuron=0; neuron<neuronsNum; neuron++)
        {
            writer.writeStartElement("Neuron");
            writer.writeAttribute("id",QString::number(neuron));
            const std::vector<double> weights = neurons.at(neuron).getWeights();
            if(weights.size()!=0)
            {
                QString tempS = QString::number(weights.at(0));
                //for each weight
                for(unsigned int w=1; w<weights.size(); w++)
                {
                    tempS += " " + QString::number(weights.at(w));
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

NeuralNetwork SaveManager::LoadNetwork(QString neuralNetworkName)
{
    std::vector<unsigned int> myV;
    myV.push_back(1);
    myV.push_back(1);
    myV.push_back(1);
    NeuralNetwork n(myV);

    const QString fileXmlName = savePath+neuralNetworkName+".xml";
    QFile* xmlFile = new QFile(fileXmlName);
    if (!xmlFile->exists())
    {   std::cout << "file does not exist" << std::endl;
    }
    if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {   std::cout << "Can't open the file" << std::endl;
    }
    QXmlStreamReader reader(xmlFile);
    std::cerr<<"file opened !"<<std::endl;/////////////////////////////////////////////////A supprimer quand debug terminé

    while (!reader.atEnd())
    {   QXmlStreamReader::TokenType token = reader.readNext();
        if (token==QXmlStreamReader::StartDocument)
        {   continue;
        }

        if (token==QXmlStreamReader::StartElement)
        {   if (reader.name()=="NeuralNetwork")
            {   this->parseNeuralNetwork(reader);
            }
        }
    }

    if (reader.hasError())
    {   std::cout << "Error in reading XML" << std::endl;
    }

    return n;

}

void SaveManager::parseNeuralNetwork(QXmlStreamReader& reader)
{   int inputsNum;
    std::vector<std::vector<std::vector<double> > > neuronWeights;
    int currentNeuronLayer;
    int currentNeuron;
    QString weights;
    std::vector<double> weightsArray;
    QXmlStreamAttributes attributes;

    if (reader.tokenType() != QXmlStreamReader::StartElement && reader.name() != "NeuralNetwork")
    {   std::cout << "Error in reading NeuralNetwork" << std::endl;
    }
    reader.readNext();
    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "NeuralNetwork"))
    {   attributes = reader.attributes();
        // Input layer management
        if (reader.name() == "NeuronLayer" && attributes.hasAttribute("id") && attributes.value("id").toString() == "0")
        {   reader.readNext();
            inputsNum=reader.readElementText().toInt();
            reader.readNext();
        } else if (reader.name() == "NeuronLayer" && attributes.hasAttribute("id"))
        // General layer management
        {   currentNeuronLayer=attributes.value("id").toInt();
            reader.readNext();
            while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "NeuralLayer"))
            {   attributes = reader.attributes();
                if (reader.name() == "Neuron" && attributes.hasAttribute("id"))
                // Neuron management
                {   currentNeuron=attributes.value("id").toInt();
                    reader.readNext();
                    while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "Neuron"))
                    {   if (reader.name() == "weights")
                        // weights management
                        {   weights=reader.readElementText();
                            parseWeights(weights,weightsArray);
                            for (unsigned int i=0;i<weightsArray.size();i++)
                            {   neuronWeights[currentNeuronLayer][currentNeuron].push_back(weightsArray[i]);
                            }
                        } else
                        // error
                        {   std::cout << "Error during the loading" << std::endl;
                        }
                    }
                } else
                // error
                {   std::cout << "Error during the loading" << std::endl;
                }

            }
        } else
        // error
        {   std::cout << "Error during the loading" << std::endl;
        }
        reader.readNext();
    }
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
