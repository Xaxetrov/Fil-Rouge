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
    const unsigned int hiddenLayerNum=nn.getLayers().size(); //nombre de couches cachées (en plus de l'input et de l'output)
    const unsigned int inputNum = nn.getInputsNum(); // nombre d'inputs

    writer.writeStartElement("NeuronLayer");
    writer.writeAttribute("id",QString::number(0)); // 0 means "input layer"
    writer.writeAttribute("inputNum", QString::number(inputNum));
    writer.writeComment("this is the input layer");
    writer.writeEndElement();

    for (unsigned int i=1; i<=hiddenLayerNum; i++)
    {
        writer.writeStartElement("NeuronLayer");
        writer.writeAttribute("id", QString::number(i));
        /**
          Informations a generer ici
          */
        writer.writeEndElement();
    }

    writer.writeStartElement("NeuronLayer");
    writer.writeAttribute("id", QString::number(hiddenLayerNum+1));
    writer.writeComment("this is the output layer");
    writer.writeEndElement();

    writer.writeEndDocument();

    fileXml.close();


    return 0;
}

NeuralNetwork SaveManager::LoadNetwork(QString neuralNetworkName)
{
    NeuralNetwork n;
    return n;
}
