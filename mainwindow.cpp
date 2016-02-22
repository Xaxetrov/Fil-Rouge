#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Animal.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set central widget
    loadWorld();
    worldWidget.setWorld(&world);
    setCentralWidget(&worldWidget);
    worldWidget.updateScene();
    //set dock widget
    QDockWidget * dockWidget = new QDockWidget(tr("Entity View"),this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setWidget(&entityWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    entityWidget.updateView();
    //(re)set menu bar
    this->menuBar()->clear();
    fileMenu = this->menuBar()->addMenu(tr("File"));
    simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
    fileExitAction = fileMenu->addAction(tr("Exit"));
    simmulationStartStopAction = simulationMenu->addAction(tr("Start simulation"));

    //event managment
    QObject::connect(&worldWidget,SIGNAL(animalSelected(Animal*)),&entityWidget,SLOT(setAnimal(Animal*)));
    QObject::connect(fileExitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    QObject::connect(simulationMenu,SIGNAL(triggered(QAction*)),this,SLOT(switchTimer()));
}

void MainWindow::loadWorld()
{
    //TODO load the world from a file or something like that

    //world = World();
    Animal * animal0 = new Animal(250,250,10,50,&world);
    Animal * animal1 = new Animal(0,0,10,50,&world);
    Animal * animal2 = new Animal(499,499,10,50,&world);
    Animal * animal3 = new Animal(0,499,10,50,&world);
    Animal * animal4 = new Animal(499,0,10,50,&world);
    Animal * animal5 = new Animal(215,025,10,50,&world);
    Animal * animal6 = new Animal(125,350,10,50,&world);
    Animal * animal7 = new Animal(350,50,10,50,&world);
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

void MainWindow::switchTimer()
{
    if(worldWidget.isSimulationRunning())
    {
        worldWidget.suspendSimulation();
        simmulationStartStopAction->setText(tr("Restart simulation"));
    }
    else
    {
        worldWidget.startSimulation();
        simmulationStartStopAction->setText(tr("Stop simulation"));
    }
}
