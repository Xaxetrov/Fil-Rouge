#include <QFileDialog>
#include <QDir>

#include "World.h"
#include "SaveManager.h"
#include "WorldCreatorResourcesWidget.h"
#include "ui_WorldCreatorResourcesWidget.h"

WorldCreatorResourcesWidget::WorldCreatorResourcesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldCreatorResourcesWidget)
{
    ui->setupUi(this);

    editorWidget.setResourcesList(&resources);

    ui->horizontalLayout_editor->addWidget(&editorWidget);

    ui->dockWidget->setWidget(&toolBox);

    ui->sl_toolSize->setRange(10,100);

    QObject::connect(ui->bt_loadWorld,SIGNAL(clicked(bool)),this,SLOT(loadWorld()));


    QObject::connect(&toolBox, SIGNAL(brushSizeChanged(int)),&editorWidget, SLOT(setCurrantRadius(int)));
    QObject::connect(&toolBox,SIGNAL(brushTypeChanged(WorldEditor::Tools)),&editorWidget,SLOT(setCurrantTool(WorldEditor::Tools)));
    QObject::connect(&toolBox, SIGNAL(worldSizeChanged()),&editorWidget, SLOT(onWorldSizeChanged()));
}

WorldCreatorResourcesWidget::~WorldCreatorResourcesWidget()
{
    delete ui;
}

void WorldCreatorResourcesWidget::loadWorld()
{
    World world = World();
    QString filter = "XML files (*.xml);;All files (*.*)";
    QString defaultFilter = "XML files (*.xml)";
    QString filePath = QFileDialog::getOpenFileName(this,tr("Load the world of your dreams"),"../save",
                                                    filter,&defaultFilter);
    SaveManager saveManager;
    saveManager.loadWorld(filePath, &world);

    //delete old animals
    std::list<std::shared_ptr<Entity>> entities = world.getEntities();
    for(std::list<std::shared_ptr<Entity>>::iterator e=entities.begin() ; e!=entities.end() ; ++e)
    {
        if(std::shared_ptr<Resource> resource = std::dynamic_pointer_cast<Resource>(*e))
        {
            resources.push_back(resource);
        }
    }
    ui->lb_loadedWorld->setText(filePath);
    editorWidget.updateScene();
}

void WorldCreatorResourcesWidget::chooseTool()
{
    if(ui->bt_water->isChecked())
        editorWidget.setCurrantTool(WorldEditor::Tools::water);
    else if(ui->bt_vegetal->isChecked())
        editorWidget.setCurrantTool(WorldEditor::Tools::vegetal);
    else if(ui->bt_meat->isChecked())
        editorWidget.setCurrantTool(WorldEditor::Tools::meat);
}

void WorldCreatorResourcesWidget::setRadius(int radius)
{
    editorWidget.setCurrantRadius(radius);
}

void WorldCreatorResourcesWidget::setQuantity(int quantity)
{
    editorWidget.setCurrantMaxQuantity(quantity);
}
