#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Animal.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadWorld();
    worldWidget.setWorld(&world);
    setCentralWidget(&worldWidget);
    worldWidget.updateScene();
}

void MainWindow::loadWorld()
{
    //TODO load the world from a file or something like that

    //world = World();
    Animal * animal1 = new Animal(10,10,10,2,&world);
    world.addEntity(animal1);
}

MainWindow::~MainWindow()
{
    delete ui;
    for(Entity* e:world.getEntities())
    {
        delete e;
    }
}
