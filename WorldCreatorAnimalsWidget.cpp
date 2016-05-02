#include "WorldCreatorAnimalsWidget.h"
#include "ui_worldcreatoranimalswidget.h"

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
