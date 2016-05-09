#include <QFileDialog>
#include <QFile>
#include <memory>

#include "WorldCreator.h"
#include "ui_WorldCreator.h"
#include "SaveManager.h"
#include "config/config.h"
#include "Herbivore.h"
#include "Carnivore.h"

WorldCreator::WorldCreator(World *worldToChange, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorldCreator),
    world(worldToChange)
{
    ui->setupUi(this);

    QLayout *animalsLayout = new QGridLayout();
    ui->tabAnimaux->setLayout(animalsLayout);
    animalsLayout->addWidget(&animalWidget);

    /*setCentralWidget(&tabWidget); //replace with a clean one
    tabWidget.addTab(&resourceWidget,tr("Resources"));
    tabWidget.addTab(&animalWidget,tr("Animaux"));*/

    QObject::connect(ui->bt_ok,SIGNAL(clicked(bool)),this,SLOT(finish()));
    QObject::connect(ui->bt_cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

WorldCreator::~WorldCreator()
{
    delete ui;
}

void WorldCreator::loadWorld()
{
    if(world == nullptr)
        return;
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load the world of your dreams"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    SaveManager saveManager;
    saveManager.loadWorld(filePath, world);

    //delete old animals
    std::list<std::shared_ptr<Entity>> entities = world->getEntities();
    for(std::list<std::shared_ptr<Entity>>::iterator e=entities.begin() ; e!=entities.end() ; ++e)
    {
        if(std::shared_ptr<Animal> animal = std::dynamic_pointer_cast<Animal>(*e))
        {
            std::list<std::shared_ptr<Entity>>::iterator sav = e;
            sav--;
            entities.erase(e);
            e=sav;
        }
    }
}

void WorldCreator::finish()
{
    if(world==nullptr)
        return;
    SaveManager saveManager;

    //set neuralnets to entities & create entities
    unsigned numH(animalWidget.getNumberOfHerbivore()), numC(animalWidget.getNumberOfCarnivore());
    world->feedWithRandomHerbivore(numH);
    std::list<std::shared_ptr<Entity>> entities = world->getEntities();
    if(animalWidget.isHerbivoreChecked())
    {
        std::list<QString>::iterator iteReseaux = herbivores.begin();
        for(std::list<std::shared_ptr<Entity>>::iterator e=entities.begin() ; e!=entities.end() ; ++e)
        {
            if(std::shared_ptr<Herbivore> herbivore = std::dynamic_pointer_cast<Herbivore>(*e))
            {
                std::cout << iteReseaux->toStdString() << std::endl;
                herbivore->setBrain(saveManager.LoadNetwork(*iteReseaux));
                iteReseaux++;
                if (iteReseaux == herbivores.end())
                {
                    iteReseaux = herbivores.begin();
                }
            }
        }
    }
    else
    {
    }
    world->feedWithRandomCarnivore(numC);
    if(animalWidget.isCarnivoreChecked())
    {
        std::list<QString>::iterator iteReseaux = carnivores.begin();
        for(std::list<std::shared_ptr<Entity>>::iterator e=entities.begin() ; e!=entities.end() ; ++e)
        {
            if(std::shared_ptr<Carnivore> carnivore = std::dynamic_pointer_cast<Carnivore>(*e))
            {
                carnivore->setBrain(saveManager.LoadNetwork(*iteReseaux));
                iteReseaux++;
                if (iteReseaux == carnivores.end())
                {
                    iteReseaux = carnivores.begin();
                }
            }
        }
    }
    else
    {
    }

    //put World in a predefined xmlFile
    QString path("../save/worldByWC.xml");
    saveManager.saveWorld(*world,path);
}

void WorldCreator::addHerbivoreBrain()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Choose a herbivore brain"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    herbivores.push_back(filePath);
}

void WorldCreator::addCarnivoreBrain()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Choose a carnivore brain"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    carnivores.push_back(filePath);
}
