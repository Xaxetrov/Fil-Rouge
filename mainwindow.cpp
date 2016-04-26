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
    fileExitAction = fileMenu->addAction(tr("Exit"));
    simmulationStartStopAction = simulationMenu->addAction(tr("Start simulation"));
    saveNeuralNetworkAction = animalMenu->addAction(tr("Save neural network as..."));
    loadNeuralNetworkAction = animalMenu->addAction(tr("Load neural network"));
    animalMenu->setEnabled(false);

    //event managment
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),&entityWidget,SLOT(setAnimal(std::weak_ptr<Animal>)));
    QObject::connect(&worldWidget,SIGNAL(animalSelected(std::weak_ptr<Animal>)),this,SLOT(setSelectedAnimal(std::weak_ptr<Animal>)) );
    QObject::connect(fileExitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    QObject::connect(simulationMenu,SIGNAL(triggered(QAction*)),this,SLOT(switchTimer()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),&entityWidget,SLOT(update()));
    QObject::connect(&worldWidget,SIGNAL(sceneUpdated()),this,SLOT(updateStatusBar()));
    QObject::connect(saveNeuralNetworkAction,SIGNAL(triggered(bool)),this,SLOT(saveNeuralNetwork()));
    QObject::connect(loadNeuralNetworkAction, SIGNAL(triggered(bool)),this, SLOT(loadNeuralNetwork()));
}

void MainWindow::loadWorld()
{
    const QString worldSave("../save/world.xml");
    loadXML(worldSave);

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

void MainWindow::loadXML(QString worldSave)
{
   QFile* xmlFile = new QFile(worldSave);
   if(!xmlFile->exists())
   {
     std::cout << "file does not exist" << std::endl;
   }

   if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
   { //error
     std::cout << "Can't open the file" << std::endl;
   }
   QXmlStreamReader reader(xmlFile);

   while(!reader.atEnd() && !reader.hasError())
   {
     QXmlStreamReader::TokenType token = reader.readNext();
     if(token == QXmlStreamReader::StartDocument)
     { continue;
     }

     if(token == QXmlStreamReader::StartElement)
     {
      if(reader.name() == "World")
      {
         this->parseWorld(reader);
      }
     }
   }
   if(reader.hasError())
   { std::cout << "Error in reading XML in constructor" << std::endl;
   }
   delete xmlFile;
}

void MainWindow::parseWorld(QXmlStreamReader& reader)
{
  int xWorld, yWorld;

  if(reader.tokenType() != QXmlStreamReader::StartElement &&
     reader.name() != "World")
  { // error
    std::cout << "Error in reading Wolrd" << std::endl;
  }
  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "World"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "x")
      {
        xWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "y")
      {
        yWorld = reader.readElementText().toInt();
      }
      else if(reader.name() == "Entity")
      {
        this->parseEntity(reader);
      }
      else
      { //error
        std::cout << "Unknown Token" << std::endl;
      }
    }
    reader.readNext();
  }
  world.setSize(xWorld,yWorld);

}

void MainWindow::parseEntity(QXmlStreamReader& reader)
{
  QString type;
  int xEntity, yEntity, radiusEntity;

  if(!reader.tokenType() == QXmlStreamReader::StartElement &&
      reader.name() == "Entity")
  { //error
  }

  QXmlStreamAttributes attributes = reader.attributes();
  if(attributes.hasAttribute("type"))
  {
    type = attributes.value("type").toString();
  }
  else
  { //error
    std::cout << "No Attribute type" << std::endl;
  }

  reader.readNext();
  while(!(reader.tokenType() == QXmlStreamReader::EndElement &&
         reader.name() == "Entity"))
  {
    if(reader.tokenType() == QXmlStreamReader::StartElement)
    {
      if(reader.name() == "x")
      {
        xEntity = reader.readElementText().toInt();
      }
      else if(reader.name() == "y")
      {
        yEntity = reader.readElementText().toInt();
      }
      else if(reader.name() == "radius")
      {
        radiusEntity = reader.readElementText().toInt();
      }
      else
      { //error
      }
    }
    reader.readNext();
  }

  if(type == "Vegetal")
  {
    shared_ptr<Vegetal> entity( make_shared<Vegetal>(xEntity, yEntity, radiusEntity, VEGETAL_MAXQUANTITY));
    world.addEntity(entity);
  }
  else if(type == "Water")
  {
    shared_ptr<Water> entity( make_shared<Water>(xEntity, yEntity, radiusEntity, WATER_MAXQUANTITY));
    world.addEntity(entity);
  }
  /*
  else
  {
    Meat * entity = new Meat(xEntity, yEntity, 0, widthEntity);
    this->addEntity(entity);
  }*/

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
    if(shared_ptr<Animal> a = selectedAnimal.lock())
        saveNeuralNetwork(a,true);
}

void MainWindow::saveNeuralNetwork(shared_ptr<Animal> a, bool pauseDuringSave)
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
    QString filePath = QFileDialog::getSaveFileName(this,tr("Save animal Neurale Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    saveManager.SaveNetwork(nn,filePath);
    if(pause)
        worldWidget.startSimulation();
}

void MainWindow::loadNeuralNetwork()
{
    if(shared_ptr<Animal> a = selectedAnimal.lock())
        loadNeuralNetwork(a,true);
}

void MainWindow::loadNeuralNetwork(shared_ptr<Animal> a, bool pauseDuringLoad)
{
    bool pause = false;
    if(pauseDuringLoad && worldWidget.isSimulationRunning())
        pause = true;
    if(pause)
        worldWidget.suspendSimulation();

    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    SaveManager saveManager;
    NeuralNetwork* newBrain = saveManager.LoadNetwork(filePath);
    a->setBrain(newBrain);
    if(pause)
        worldWidget.startSimulation();
}
