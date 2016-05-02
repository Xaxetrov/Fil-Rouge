#include "WorldCreatorAnimalsWidget.h"
#include "ui_WorldCreatorAnimalsWidget.h"

WorldCreatorAnimalsWidget::WorldCreatorAnimalsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldCreatorAnimalsWidget)
{
    ui->setupUi(this);
}

WorldCreatorAnimalsWidget::~WorldCreatorAnimalsWidget()
{
    delete ui;
}

void WorldCreatorAnimalsWidget::addToHerbivoreList(QString path)
{

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
