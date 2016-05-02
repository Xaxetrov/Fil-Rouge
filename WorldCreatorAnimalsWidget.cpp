#include "WorldCreatorAnimalsWidget.h"
#include "ui_WorldCreatorAnimalsWidget.h"

#include <QFileDialog>
#include <iostream>

#include "SaveManager.h"

WorldCreatorAnimalsWidget::WorldCreatorAnimalsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldCreatorAnimalsWidget)
{
    ui->setupUi(this);

    herbivoreListModel = new QStringListModel(this);
    carnivoreListModel = new QStringListModel(this);

    herbivoreListModel->setStringList(herbivoreList);
    carnivoreListModel->setStringList(carnivoreList);


    QObject::connect(ui->bt_addHerbivore,SIGNAL(clicked(bool)),this,SLOT(addHerbivore()));
    QObject::connect(ui->bt_addCarnivore,SIGNAL(clicked(bool)),this,SLOT(addCarnivore()));
}

WorldCreatorAnimalsWidget::~WorldCreatorAnimalsWidget()
{
    delete ui;
}

void WorldCreatorAnimalsWidget::addHerbivore()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load herbivore neural network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    if(filePath != "")
    {
        addToHerbivoreList(filePath);
    }
}

void WorldCreatorAnimalsWidget::addCarnivore()
{
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load carnivore neural network"),QDir::currentPath(),
                                                    filter,&defaultFilter);
    if(filePath != "")
    {
        addToCarnivoreList(filePath);
    }
}

/*void WorldCreatorAnimalsWidget::removeSelectedHerbivore()
{

}*/


void WorldCreatorAnimalsWidget::addToHerbivoreList(QString path)
{
    herbivoreList << path;
}

void WorldCreatorAnimalsWidget::addToCarnivoreList(QString path)
{
    carnivoreList << path;
}

void WorldCreatorAnimalsWidget::removeFromHerbivoreList(int index)
{
    herbivoreList.removeAt(index);
}

void WorldCreatorAnimalsWidget::removeFromCarnivoreList(int index)
{
    carnivoreList.removeAt(index);
}


bool WorldCreatorAnimalsWidget::isHerbivoreChecked()
{
    return ui->gb_Herbivore->isChecked();
}

bool WorldCreatorAnimalsWidget::isCarnivoreChecked()
{
    return ui->gb_carnivore->isChecked();
}

unsigned WorldCreatorAnimalsWidget::getNumberOfHerbivore()
{
    return ui->sb_herbivore->value();
}

unsigned WorldCreatorAnimalsWidget::getNumberOfCarnivore()
{
    return ui->sb_herbivore->value();
}
