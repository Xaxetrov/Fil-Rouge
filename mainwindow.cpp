#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Animal.h"
#include "config/config.h"
#include <cmath>
#include <sstream>

#include <QDockWidget>
#include <QKeyEvent>
#include <QFileDialog>

#include "Vegetal.h"
#include "Water.h"
#include "Meat.h"
#include "Carnivore.h"
#include "Herbivore.h"
#include "SaveManager.h"

#include <QFile>

//DEBUG
#include <iostream>
#include <cstdlib>
#include <ctime>


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
    //entityWidget.updateView();
    entityWidget.update();
    //(re)set menu bar
    this->menuBar()->clear();
    fileMenu = this->menuBar()->addMenu(tr("File"));
    simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
    animalMenu = this->menuBar()->addMenu(tr("Animal"));
    settingsMenu = this->menuBar()->addMenu(tr("Settings"));
    fileExitAction = fileMenu->addAction(tr("Exit"));
    saveWorldAction = fileMenu->addAction(tr("Save world as..."));
    loadWorldAction = fileMenu->addAction(tr("Load world"));
    openWorldCreatorAction = fileMenu->addAction(tr("Open World Creator tool"));
    openTimelineAction = fileMenu->addAction(tr("Open timeline"));
    simmulationStartStopAction = simulationMenu->addAction(tr("Start simulation"));
    saveNeuralNetworkAction = animalMenu->addAction(tr("Save neural network as..."));
    loadNeuralNetworkAction = animalMenu->addAction(tr("Load neural network"));
    setParameters = settingsMenu->addAction(tr("Parameters"));
    animalMenu->setEnabled(false);

    parameterswidget.set(&world, &worldWidget);

    //event managment
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),&entityWidget,SLOT(setAnimal(std::weak_ptr<Animal>)));
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),this,SLOT(setSelectedAnimal(std::weak_ptr<Animal>)) );
    QObject::connect(fileExitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    QObject::connect(simulationMenu,SIGNAL(triggered(QAction*)),this,SLOT(switchTimer()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),&entityWidget,SLOT(update()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),this,SLOT(updateStatusBar()));
    QObject::connect(saveNeuralNetworkAction,SIGNAL(triggered(bool)),this,SLOT(saveNeuralNetwork()));
    QObject::connect(loadNeuralNetworkAction, SIGNAL(triggered(bool)),this, SLOT(loadNeuralNetwork()));
    QObject::connect(saveWorldAction, SIGNAL(triggered(bool)),this, SLOT(saveWorld()));
    QObject::connect(loadWorldAction, SIGNAL(triggered(bool)),this, SLOT(loadWorldSave()));
    QObject::connect(openWorldCreatorAction, SIGNAL(triggered(bool)), this, SLOT(openWorldCreator()));
    QObject::connect(&worldCreator, SIGNAL(actionFinished()), this, SLOT(onWorldCreatorClosed()));
    QObject::connect(&worldCreator, SIGNAL(newWorldGenerated(QString)), this, SLOT(onWorldCreatorNewWorldGenerated(QString)));
    QObject::connect(openTimelineAction, SIGNAL(triggered(bool)), this, SLOT(openTimeline()));
    QObject::connect(setParameters, SIGNAL(triggered(bool)), this, SLOT(openParametersWidget()));
}

//custom load for debug
void MainWindow::loadWorld()
{
    const QString savingPath("../save/world.xml");
    SaveManager saveManager;
    world = saveManager.loadWorld(savingPath);

  /*  Animal * animal0 = new Animal(130,278,10,50,&world);
    Animal * animal1 = new Animal(160,278,10,50,&world);
    world.addEntity(animal0);
    world.addEntity(animal1);
    Animal * animal2 = new Animal(99,319,10,50,&world);
    Animal * animal3 = new Animal(40,99,10,50,&world);
    Animal * animal4 = new Animal(199,236,10,50,&world);
    Animal * animal5 = new Animal(215,025,10,50,&world);
    Animal * animal6 = new Animal(125,350,10,50,&world);
    Animal * animal7 = new Animal(350,50,10,50,&world);

    world.addEntity(animal2);
    world.addEntity(animal3);
    world.addEntity(animal4);
    world.addEntity(animal5);
    world.addEntity(animal6);
    world.addEntity(animal7);*/

    //random generator
//
    srand(std::time(0));
    //world.feedWithRandomAnimal(40);
    world.feedWithRandomHerbivore(20);
    world.feedWithRandomCarnivore(7);

    /*shared_ptr<Animal> male(make_shared<Animal>(100, 250, 10, 50, 2, &world, false) );
    shared_ptr<Animal> female(make_shared<Animal>(300, 250, 10, 50, 2, &world, true) );
    female->turn(PI);

    world.addEntity(male);
    world.addEntity(female);*/

/*Animal * animal = new Animal(1.46671, 491.343,10,50,&world);
animal->turn(3.17);
world.addEntity(animal);*/
    /*Animal * animal0 = new Animal(400,450,10,50,&world);
    Animal * animal1 = new Animal(180,60,10,50,&world);
    Animal * animal2 = new Animal(350,120,10,50,&world);
    animal0->turn(PI/2);
    animal2->turn(PI);

    world.addEntity(animal0);
    world.addEntity(animal1);
    world.addEntity(animal2);
    Animal * animal3 = new Animal(100,200,10,50,&world);
    Animal * animal4 = new Animal(200,200,10,50,&world);
    animal4->turn(PI);

//    world.addEntity(animal3);
//    world.addEntity(animal4);

    world.addEntity(animal3);
    world.addEntity(animal4);*/

}


MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Space)
    {
        switchTimer();
    }
    else if(e->key()==Qt::Key_Enter || e->key()==Qt::Key_Return)
    {
        if(!worldWidget.isSimulationRunning())
        {
            worldWidget.tick();
        }
    }
}

void MainWindow::setSelectedAnimal(std::weak_ptr<Animal> a)
{
    selectedAnimal = a;
    //enable or disable the animal menu
    if(a.use_count()!=0)
    {
        animalMenu->setEnabled(true);
    }
    else
    {
        animalMenu->setEnabled(false);
    }
}

void MainWindow::updateStatusBar()
{
    QString message = tr("number of living: %1 Age of the World: %2 ticks").arg(world.getNumberOfLiving()).arg(world.getWorldAge());
    this->statusBar()->showMessage(message);
}

void MainWindow::saveNeuralNetwork()
{
    if(std::shared_ptr<Animal> a = selectedAnimal.lock())
        saveNeuralNetwork(a,true);
}

void MainWindow::saveNeuralNetwork(std::shared_ptr<Animal> a, bool pauseDuringSave)
{
    bool pause = false;
    if(pauseDuringSave && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();
    NeuralNetwork nn = *(a->getBrain()); //copy the neural network
    SaveManager saveManager;
    /*QFileDialog fileDialog(this,tr("Save animal Neurale Network"));
    fileDialog.setDefaultSuffix("xml");*/
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save animal Neurale Network"),"../save",
                                                    filter,&defaultFilter);
    if(filePath!="")
        saveManager.SaveNetwork(nn,filePath);

    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::loadNeuralNetwork()
{
    if(std::shared_ptr<Animal> a = selectedAnimal.lock())
        loadNeuralNetwork(a,true);
}

void MainWindow::loadNeuralNetwork(std::shared_ptr<Animal> a, bool pauseDuringLoad)
{
    bool pause = false;
    if(pauseDuringLoad && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),"../save",
                                                    filter,&defaultFilter);
    if(filePath!="")
    {
        SaveManager saveManager;
        NeuralNetwork* newBrain = saveManager.LoadNetwork(filePath);
        a->setBrain(newBrain);
    }

    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::saveWorld(bool pauseDuringSave)
{
    bool pause = false;
    if(pauseDuringSave && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    SaveManager saveManager;
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save animal Neurale Network"),"../save",
                                                    filter,&defaultFilter);
    if(filePath != "")
        saveManager.saveWorld(world,filePath);

    if(pause)
            worldWidget.startSimulation();
}

void MainWindow::loadWorldSave(bool pauseDuringLoad)
{
    bool pause = false;
    if(pauseDuringLoad && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),"../save",
                                                    filter,&defaultFilter);
    if(filePath != "")
    {
        SaveManager saveManager;
        world = World();
        saveManager.loadWorld(filePath,&world);
        worldWidget.setWorld(&world);
    }


    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::openWorldCreator()
{
    worldWidget.suspendSimulation();
    //worldCreator.setWorldPointer(&world);
    worldCreator.show();
    /*
     * include code here
     */
}

void MainWindow::onWorldCreatorClosed()
{
    //worldWidget.startSimulation();
}

void MainWindow::onWorldCreatorNewWorldGenerated(QString path)
{
    if(path != "")
    {
        SaveManager saveManager;
        world = World();
        saveManager.loadWorld(path,&world);
        worldWidget.setWorld(&world);
    }
}

void MainWindow::openTimeline()
{
    timeline.show();
}

void MainWindow::openParametersWidget()
{
    parameterswidget.show();
}
