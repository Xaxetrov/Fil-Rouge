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
    Animal * animal0 = new Animal(250,250,10,2,&world);
    Animal * animal1 = new Animal(0,0,10,2,&world);
    Animal * animal2 = new Animal(499,499,10,2,&world);
    Animal * animal3 = new Animal(0,499,10,2,&world);
    Animal * animal4 = new Animal(499,0,10,2,&world);
    Animal * animal5 = new Animal(215,025,10,2,&world);
    Animal * animal6 = new Animal(125,350,10,2,&world);
    Animal * animal7 = new Animal(350,50,10,2,&world);
    world.addEntity(animal0);
    world.addEntity(animal1);
    world.addEntity(animal2);
    world.addEntity(animal3);
    world.addEntity(animal4);
    world.addEntity(animal5);
    world.addEntity(animal6);
    world.addEntity(animal7);
}

MainWindow::~MainWindow()
{
    delete ui;
    for(Entity* e:world.getEntities())
    {
        delete e;
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
void MainWindow::on_actionStartTimer_triggered()
{
    worldWidget.startSimulation();
}
void MainWindow::on_actionStop_triggered()
{
    worldWidget.suspendSimulation();
}

