#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Animal.h"
#include <QDockWidget>

#include "Vegetal.h"
#include "Water.h"

#include <QFile>

//DEBUG
#include <iostream>


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


    const QString worldSave("../save/world.xml");
    loadXML(worldSave);

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
    Vegetal * entity = new Vegetal(xEntity, yEntity, radiusEntity);
    world.addEntity(entity);
  }
  else if(type == "Water")
  {
    Water * entity = new Water(xEntity, yEntity, radiusEntity);
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
