#include "SaveManager.h"

#include <QFile>
#include <QtXml>
#include <iostream>

SaveManager::SaveManager()
{
}

int SaveManager::SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName)
{
    /*QString fileName = savePath+neuralNetworkName+".xml";
    QDomDocument dom(neuralNetworkName);
    QFile doc_xml(fileName);
    std::cerr << fileName.toStdString();
    if(!doc_xml.open(QIODevice::ReadWrite))
    {
        std::cerr << "impossible d'ouvrir le XML1" << std::endl;
        doc_xml.close();
        return 1;
    }
    if(!dom.setContent(&doc_xml))
    {
        std::cerr << "impossible d'ouvrir le XML2" << std::endl;
        doc_xml.close();
        return 2;
    }
    doc_xml.close();*/


    QString fileXmlName = savePath+neuralNetworkName+".xml";
    QFile fileXml(fileXmlName);

    // Ouverture du fichier en Ã©criture et en texte. (sort de la fonction si le fichier ne s'ouvre pas)
    if(!fileXml.open(QFile::WriteOnly | QFile::Text))
    {   return false;
    }
    QXmlStreamWriter writer(&fileXml);

    // Active l'indentation automatique du fichier XML pour une meilleur visibilitÃ©
    writer.setAutoFormatting(true);

    // Insert la norme de codification du fichier XML :
    writer.writeStartDocument();

    // Ã‰lÃ©ment racine du fichier XML
    writer.writeStartElement("NeuronalNetwork");

    int m_hiddenLayerNum=5;   // arbitraire

    writer.writeStartElement("NeuronLayer");
    writer.writeStartElement("NeuronLayerNumber");
    writer.writeCharacters("inputLayer");
    writer.writeEndElement();
    writer.writeEndElement();

    for (int i=0;i<m_hiddenLayerNum;i++)
    {   writer.writeStartElement("NeuronLayer");
        writer.writeStartElement("NeuronLayerNumber");
        writer.writeCharacters(QString::number(1));
        writer.writeEndElement();
        writer.writeEndElement();
    }

    writer.writeStartElement("NeuronLayer");
    writer.writeStartElement("NeuronLayerNumber");
    writer.writeCharacters("outputLayer");
    writer.writeEndElement();
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
