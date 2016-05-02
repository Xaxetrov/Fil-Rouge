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

    ui->lv_herbivore->setModel(herbivoreListModel);
    ui->lv_carnivore->setModel(carnivoreListModel);


    QObject::connect(ui->bt_addHerbivore,SIGNAL(clicked(bool)),this,SLOT(addHerbivore()));
    QObject::connect(ui->bt_addCarnivore,SIGNAL(clicked(bool)),this,SLOT(addCarnivore()));
    QObject::connect(ui->bt_removeHerbivore,SIGNAL(clicked(bool)),this,SLOT(removeSelectedHerbivore()));
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

void WorldCreatorAnimalsWidget::removeSelectedHerbivore()
{
    QModelIndexList list = ui->lv_herbivore->selectionModel()->selectedIndexes();

    for(QModelIndex &index : list)
    {
        removeFromHerbivoreList(index.row());
    }
}


void WorldCreatorAnimalsWidget::addToHerbivoreList(QString path)
{
    herbivoreList << path;
    herbivoreListModel->setStringList(herbivoreList);
}

void WorldCreatorAnimalsWidget::addToCarnivoreList(QString path)
{
    carnivoreList << path;
    carnivoreListModel->setStringList(carnivoreList);
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
