#include "WorldCreator.h"
#include "ui_WorldCreator.h"

WorldCreator::WorldCreator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WorldCreator)
{
    ui->setupUi(this);
}

WorldCreator::~WorldCreator()
{
    delete ui;
}
