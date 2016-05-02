#include "WorldCreatorResourcesWidget.h"
#include "ui_WorldCreatorResourcesWidget.h"

WorldCreatorResourcesWidget::WorldCreatorResourcesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldCreatorResourcesWidget)
{
    ui->setupUi(this);
}

WorldCreatorResourcesWidget::~WorldCreatorResourcesWidget()
{
    delete ui;
}
