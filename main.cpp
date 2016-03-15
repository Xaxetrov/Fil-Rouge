#include "mainwindow.h"
#include <QApplication>

#include <cmath>
#include "config/config.h"

#include "SaveManager.h"

int main(int argc, char *argv[])
{
/*    std::vector<unsigned int> myTestVector;
    myTestVector.push_back(3);
    myTestVector.push_back(5);
    myTestVector.push_back(2);
    NeuralNetwork n(myTestVector);

    SaveManager s;
    QString saveName = "test";
    int r = s.SaveNetwork(n, saveName);
    s.LoadNetwork(saveName);
*/


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    // Tests save and load
    /*int inputsNum=3;
    std::vector<double> neuron10 = {0.1842,0.9685,0.1348};
    std::vector<double> neuron11 = {0.8462,0.7894,0.3214};
    std::vector<double> neuron12 = {0.9581,0.1685,0.3692};
    std::vector<double> neuron13 = {0.1654,0.9632,0.1475};
    std::vector<double> neuron14 = {0.1685,0.9748,0.6251};
    std::vector<double> neuron20 = {0.1385,0.1147,0.2568,0.1347,0.9632};
    std::vector<double> neuron21 = {0.1954,0.1384,0.3695,0.1348,0.1345};
    std::vector<double> neuron22 = {0.7412,0.3285,0.6392,0.1234,0.1387};
    std::vector<double> neuron23 = {0.7492,0.9548,0.1648,0.9648,0.1237};
    std::vector<std::vector<std::vector<double> > > neuronWeights;
    std::vector<std::vector<double> > layer1;
    std::vector<std::vector<double> > layer2;
    layer1.push_back(neuron10);
    layer1.push_back(neuron11);
    layer1.push_back(neuron12);
    layer1.push_back(neuron13);
    layer1.push_back(neuron14);
    layer2.push_back(neuron20);
    layer2.push_back(neuron21);
    layer2.push_back(neuron22);
    layer2.push_back(neuron23);
    neuronWeights.push_back(layer1);
    neuronWeights.push_back(layer2);
    QString save1 = "./../Fil-Rouge/save/testSave1.xml";
    QString save2 = "./../Fil-Rouge/save/testSave2.xml";
    NeuralNetwork n1(inputsNum,neuronWeights);
    SaveManager s;
    s.SaveNetwork(n1,save1);
    NeuralNetwork n2=s.LoadNetwork(save1);
    s.SaveNetwork(n2,save2);*/

    return 0;
}


