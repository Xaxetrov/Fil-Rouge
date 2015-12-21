#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "World.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test of entity coordinates ... OK
    Entity e(10,10,0);
    e.setCoordinate(20,20);
    std::cout << e.getX() << " " << e.getY() << std::endl;

    return a.exec();
}
