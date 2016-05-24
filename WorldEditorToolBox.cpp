#include "WorldEditorToolBox.h"
#include "ui_WorldEditorToolBox.h"
#include "config/config.h"

WorldEditorToolBox::WorldEditorToolBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorldEditorToolBox)
{
    ui->setupUi(this);

    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),ui->spinBoxBrushSize,SLOT(setValue(int)));
    QObject::connect(ui->spinBoxBrushSize,SIGNAL(valueChanged(int)),ui->horizontalSlider,SLOT(setValue(int)));
    QObject::connect(ui->horizontalSlider_Quantity,SIGNAL(valueChanged(int)),ui->spinBoxQuantity,SLOT(setValue(int)));
    QObject::connect(ui->spinBoxQuantity,SIGNAL(valueChanged(int)),ui->horizontalSlider_Quantity,SLOT(setValue(int)));

    QObject::connect(ui->sb_worldX,SIGNAL(valueChanged(int)),this,SLOT(emitWorldSize()));
    QObject::connect(ui->sb_worldY,SIGNAL(valueChanged(int)),this,SLOT(emitWorldSize()));
    QObject::connect(ui->spinBoxBrushSize,SIGNAL(valueChanged(int)),this,SLOT(emitBrushSize()));
    QObject::connect(ui->spinBoxQuantity,SIGNAL(valueChanged(int)),this,SLOT(emitBrushQuantity()));
    QObject::connect(ui->rb_Water,SIGNAL(clicked(bool)),this,SLOT(emitBrushType()));
    QObject::connect(ui->rb_Vegetal,SIGNAL(clicked(bool)),this,SLOT(emitBrushType()));
    QObject::connect(ui->rb_Meat,SIGNAL(clicked(bool)),this,SLOT(emitBrushType()));
}

WorldEditorToolBox::~WorldEditorToolBox()
{
    delete ui;
}

void WorldEditorToolBox::emitBrushSize()
{
    emit brushSizeChanged(ui->spinBoxBrushSize->value());
}

void WorldEditorToolBox::emitBrushType()
{
    if(ui->rb_Water->isChecked())
    {
        emit brushTypeChanged(WorldEditor::Tools::water);
    }
    else if(ui->rb_Vegetal->isChecked())
    {
        emit brushTypeChanged(WorldEditor::Tools::vegetal);
    }
    else
    {
        emit brushTypeChanged(WorldEditor::Tools::meat);
    }
}

void WorldEditorToolBox::emitWorldSize()
{
    config::WORLD_SIZE_X = ui->sb_worldX->value();
    config::WORLD_SIZE_Y = ui->sb_worldY->value();
    emit worldSizeChanged();
}

void WorldEditorToolBox::emitBrushQuantity()
{
    emit brushQuantityChanged(ui->spinBoxQuantity->value());
}

void WorldEditorToolBox::setWorldSize(int x, int y)
{
    ui->sb_worldX->setValue(x);
    ui->sb_worldY->setValue(y);
}
