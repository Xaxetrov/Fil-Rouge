#include "mainwindow.h"
#include <QApplication>

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

    return 0;
}
