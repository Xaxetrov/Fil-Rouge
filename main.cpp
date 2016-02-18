#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "World.h"
#include "SaveManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*NeuralNetwork n;
    SaveManager s;
    QString saveName = "test";
    int r = s.SaveNetwork(n, saveName);

    return r;*/
    return a.exec();
}

