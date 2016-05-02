#include <QFileDialog>
#include <QFile>

#include "WorldCreator.h"
#include "ui_WorldCreator.h"
#include "SaveManager.h"

WorldCreator::WorldCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorldCreator),
    world(World())
{
    ui->setupUi(this);

    ui->tabWidget = QTabWidget(this); //replace with a clean one
    ui->tabWidget->addTab(&resourceWidget,tr("Resources"));
    ui->tabWidget->addTab(&animalWidget,tr("Animaux"));
}

WorldCreator::~WorldCreator()
{
    delete ui;
}

void WorldCreator::loadWorld()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    SaveManager saveManager;
    world = saveManager.loadWorld(filePath);
}

void WorldCreator::finish()
{
    SaveManager saveManager;
    QString path("../save/worldByWC.xml");
    saveManager.saveWorld(world,path);
}

void WorldCreator::addHerbivoreBrain()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    herbivores.push_back(filePath);
}

void WorldCreator::addCarnivoreBrain()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load animal Neural Network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    carnivores.push_back(filePath);
}
