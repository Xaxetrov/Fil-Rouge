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
    QLayout *resourcesLayout = new QGridLayout();
    ui->tabResources->setLayout(resourcesLayout);
    ui->tabAnimaux->setLayout(animalsLayout);
    resourcesLayout->addWidget(&resourceWidget);
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

void WorldCreator::finish()
{
    if(world==nullptr)
        return;
    SaveManager saveManager;
    *world = World();

    //TODO add code for ressources generation here
    std::list<std::shared_ptr<Resource>> resources = resourceWidget.getResources();
    for(std::list<std::shared_ptr<Resource>>::iterator iteResources = resources.begin(); iteResources!=resources.end(); ++iteResources)
    {
        world->addEntity(*iteResources);
    }

    //set neuralnets to entities & create entities
    unsigned numH(animalWidget.getNumberOfHerbivore()), numC(animalWidget.getNumberOfCarnivore());
    world->feedWithRandomHerbivore(numH);
    std::list<std::shared_ptr<Entity>> entities = world->getEntities();
    if(animalWidget.isHerbivoreChecked())
    {
        QStringList herbivores = animalWidget.getHerbivoreList();
        QStringList::iterator iteReseaux = herbivores.begin();
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
        QStringList carnivores = animalWidget.getCarnivoreList();
        QStringList::iterator iteReseaux = carnivores.begin();
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
    QString path(".");
    saveManager.saveWorld(*world,path);
    this->close();
}

void WorldCreator::closeEvent(QCloseEvent *e)
{
    emit actionFinished();
    QMainWindow::closeEvent(e);
}
