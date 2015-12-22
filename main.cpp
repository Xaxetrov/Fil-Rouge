#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "World.h"
#include "Neuron.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test of entity coordinates ... OK
    /*Entity e(10,10,0);
    e.setCoordinate(20,20);
    std::cout << e.getX() << " " << e.getY() << std::endl;*/

    //test of random between -1 and +1 .. OK
    /*srand( time( NULL ) );
    for(int i =0; i<100; i++)
    {
        Neuron e(0);
        std::cout << e.RandomWeight() << std::endl;
    }*/

    return a.exec();
}

