#include "ParametersWidget.h"
#include "ui_ParametersWidget.h"
#include "config/config.h"

#include <iostream>
using namespace std;

ParametersWidget::ParametersWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ParametersWidget)
{
    ui->setupUi(this);

    QObject::connect(ui->buttonUI,SIGNAL(clicked(bool)),this,SLOT(updateUIParam()));
    QObject::connect(ui->buttonWorld,SIGNAL(clicked(bool)),this,SLOT(updateWorldParam()));
    QObject::connect(ui->buttonResources,SIGNAL(clicked(bool)),this,SLOT(updateResourcesParam()));
    QObject::connect(ui->buttonAnimals,SIGNAL(clicked(bool)),this,SLOT(updateAnimalsParam()));
    QObject::connect(ui->buttonHerbivores,SIGNAL(clicked(bool)),this,SLOT(updateHerbivoresParam()));
    QObject::connect(ui->buttonCarnivores,SIGNAL(clicked(bool)),this,SLOT(updateCarnivoresParam()));
    QObject::connect(ui->buttonNN,SIGNAL(clicked(bool)),this,SLOT(updateNeuralNetworksParam()));
}

void ParametersWidget::set(World * world, WorldWidget * worldWidget)
{
  m_world = world;
  m_worldWidget = worldWidget;
}

// When the user opens the window, the constants are read.
void ParametersWidget::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    ui->updateInterval->setText(QString::number(config::UPDATE_TIMER_INTERVALE));
    ui->FPS->setText(QString::number(config::FPS));
    ui->nbThreads->setText(QString::number(config::NB_THREADS));
    ui->worldWidth->setText(QString::number(config::WORLD_SIZE_X));
    ui->worldHeight->setText(QString::number(config::WORLD_SIZE_Y));
    ui->minNumberHerbivores->setText(QString::number(config::MIN_NUMBER_OF_HERBVORE));
    ui->minNumberCarnivores->setText(QString::number(config::MIN_NUMBER_OF_CARNIVORE));
    ui->vegetalMaxQuantity->setText(QString::number(config::VEGETAL_MAXQUANTITY));
    ui->waterMaxQantity->setText(QString::number(config::WATER_MAXQUANTITY));
    ui->vegetalEvolution->setText(QString::number(config::EVOLUTION_VEGETAL));
    ui->waterEvolution->setText(QString::number(config::EVOLUTION_WATER));
    ui->meatEvolution->setText(QString::number(config::EVOLUTION_MEAT));
    ui->initialRadius->setText(QString::number(config::INITIAL_RADIUS));
    ui->animalMaxSpeed->setText(QString::number(config::MAX_SPEED));
    ui->maxHunger->setText(QString::number(config::MAX_HUNGER));
    ui->maxFear->setText(QString::number(config::MAX_FEAR));
    ui->maxMating->setText(QString::number(config::MAX_MATING));
    ui->defaultEnergy->setText(QString::number(config::MAX_ENERGY));
    ui->attackAngle->setText(QString::number(config::MAX_ATTACK_ANGLE));
    ui->maxHealth->setText(QString::number(config::MAX_HEALTH));
    ui->maxThirst->setText(QString::number(config::MAX_THIRST));
    ui->maxChildren->setText(QString::number(config::MAX_CHILD_PER_ANIMAL));
    ui->maxSpeedEating->setText(QString::number(config::MAX_SPEED_TO_EAT));
    ui->energyRecup->setText(QString::number(config::ENERGY_RECUP));
    ui->herbivoreFatnessEvolution->setText(QString::number(config::FATNESS_HERBIVORE));
    ui->herbivoreAttack->setText(QString::number(config::ATTACK_HERBIVORE));
    ui->carnivoreFatnessEvolution->setText(QString::number(config::FATNESS_CARNIVORE));
    ui->carnivoreAttack->setText(QString::number(config::ATTACK_CARNIVORE));
    ui->weightChangeProbability->setText(QString::number(config::NN_WEIGHT_CHANGE_PROBABILITY));
    ui->weightChangeAverageValue->setText(QString::number(config::NN_WEIGHT_CHANGE_AVERAGE_VALUE));
    ui->weightChangeStandartDeviation->setText(QString::number(config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION));
}

// Tab "User Interface"
void ParametersWidget::updateUIParam()
{
  config::UPDATE_TIMER_INTERVALE = ui->updateInterval->text().toDouble();
  config::FPS = ui->FPS->text().toDouble();
  config::NB_THREADS = ui->nbThreads->text().toDouble();
  m_worldWidget->updateTimerInterval();
}

// Tab "World"
void ParametersWidget::updateWorldParam()
{
  if(config::WORLD_SIZE_X != ui->worldWidth->text().toDouble() || config::WORLD_SIZE_Y != ui->worldHeight->text().toDouble())
  {
    config::WORLD_SIZE_X = ui->worldWidth->text().toDouble();
    config::WORLD_SIZE_Y = ui->worldHeight->text().toDouble();
    m_world->setSize(config::WORLD_SIZE_X, config::WORLD_SIZE_Y);
  }
  config::MIN_NUMBER_OF_HERBVORE = ui->minNumberHerbivores->text().toDouble();
  config::MIN_NUMBER_OF_CARNIVORE = ui->minNumberCarnivores->text().toDouble();
}

// Tab "Resources"
void ParametersWidget::updateResourcesParam()
{
  config::VEGETAL_MAXQUANTITY = ui->vegetalMaxQuantity->text().toDouble();
  config::WATER_MAXQUANTITY = ui->waterMaxQantity->text().toDouble();
  config::EVOLUTION_VEGETAL = ui->vegetalEvolution->text().toDouble();
  config::EVOLUTION_WATER = ui->waterEvolution->text().toDouble();
  config::EVOLUTION_MEAT = ui->meatEvolution->text().toDouble();
}

// Tab "Animals"
void ParametersWidget::updateAnimalsParam()
{
  config::INITIAL_RADIUS = ui->initialRadius->text().toDouble();
  config::MAX_SPEED = ui->animalMaxSpeed->text().toDouble();
  config::MAX_HUNGER = ui->maxHunger->text().toDouble();
  config::MAX_FEAR = ui->maxFear->text().toDouble();
  config::MAX_MATING = ui->maxMating->text().toDouble();
  config::MAX_ENERGY = ui->defaultEnergy->text().toDouble();
  config::MAX_ATTACK_ANGLE = ui->attackAngle->text().toDouble();
  config::MAX_HEALTH = ui->maxHealth->text().toDouble();
  config::MAX_THIRST = ui->maxThirst->text().toDouble();
  config::MAX_CHILD_PER_ANIMAL = ui->maxChildren->text().toDouble();
  config::MAX_SPEED_TO_EAT = ui->maxSpeedEating->text().toDouble();
  config::ENERGY_RECUP = ui->energyRecup->text().toDouble();
}

// Tab "Herbivores"
void ParametersWidget::updateHerbivoresParam()
{
  config::FATNESS_HERBIVORE = ui->herbivoreFatnessEvolution->text().toDouble();
  config::ATTACK_HERBIVORE = ui->herbivoreAttack->text().toDouble();
}

// Tab "Carnivores"
void ParametersWidget::updateCarnivoresParam()
{
  config::FATNESS_CARNIVORE = ui->carnivoreFatnessEvolution->text().toDouble();
  config::ATTACK_CARNIVORE = ui->carnivoreAttack->text().toDouble();
}

// Tab "Neural Networks"
void ParametersWidget::updateNeuralNetworksParam()
{
  config::NN_WEIGHT_CHANGE_PROBABILITY = ui->weightChangeProbability->text().toDouble();
  config::NN_WEIGHT_CHANGE_AVERAGE_VALUE = ui->weightChangeAverageValue->text().toDouble();
  config::NN_WEIGHT_CHANGE_SDANTARD_DEVIATION = ui->weightChangeStandartDeviation->text().toDouble();
}

ParametersWidget::~ParametersWidget()
{
    delete ui;
}
