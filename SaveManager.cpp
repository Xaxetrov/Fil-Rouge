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
    writer.writeStartElement("NeuronalNetwork");

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

    QXmlStreamReader reader;
    QString fileXmlName = savePath+neuralNetworkName+".xml";
    QFile file(fileXmlName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {   std::cerr << "Error cannot read file " << qPrintable(fileXmlName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
    }

    reader.setDevice(&file);

    reader.readNext();

    while(!reader.atEnd())
    {   // TODO
    }

    if (reader.hasError())
    {   std::cerr << "Error: Failed to parse file "
                    << qPrintable(fileXmlName) << ": "
                    << qPrintable(reader.errorString()) << std::endl;
    } else if (file.error() != QFile::NoError)
    {   std::cerr << "Error: Cannot read file " << qPrintable(fileXmlName)
                     << ": " << qPrintable(file.errorString())
                     << std::endl;
    }

    return n;

}
