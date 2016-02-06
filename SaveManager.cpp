#include "SaveManager.h"

#include <QFile>
#include <QtXml>
#include <iostream>

SaveManager::SaveManager()
{
}

int SaveManager::SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName)
{
    QString fileName = savePath+neuralNetworkName+".xml";
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
    doc_xml.close();

    return 0;
}

NeuralNetwork SaveManager::LoadNetwork(QString neuralNetworkName)
{
    NeuralNetwork n;
    return n;
}
