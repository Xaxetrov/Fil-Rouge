#include "WorldCreator.h"
#include "ui_WorldCreator.h"

WorldCreator::WorldCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorldCreator)
{
    ui->setupUi(this);

    ui->tabWidget = QTabWidget; //replace with a clean one
    ui->tabWidget->addTab(&resourceWidget,tr("Resources"));
    ui->tabWidget->addTab(&animalWidget,tr("Animaux"));
}

WorldCreator::~WorldCreator()
{
    delete ui;
}
