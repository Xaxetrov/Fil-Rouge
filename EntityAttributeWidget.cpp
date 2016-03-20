#include "EntityAttributeWidget.h"

EntityAttributeWidget::EntityAttributeWidget()
{
   //animal = weak_ptr<Animal>(); // Avoid random crashes

   defaultLabel = new QLabel("No entity selected");

   healthLabel = new QLabel();
   hungerLabel = new QLabel();
   thirstLabel = new QLabel();
   fearLabel = new QLabel();

   layout = new QVBoxLayout();
   layout->addWidget(defaultLabel);
   layout->addWidget(healthLabel);
   layout->addWidget(hungerLabel);
   layout->addWidget(thirstLabel);
   layout->addWidget(fearLabel);

   healthLabel->setVisible(false);
   hungerLabel->setVisible(false);
   thirstLabel->setVisible(false);
   fearLabel->setVisible(false);

   this->setLayout(layout);
}

EntityAttributeWidget::~EntityAttributeWidget()
{
   delete layout;
   delete healthLabel;
   delete hungerLabel;
   delete thirstLabel;
   delete fearLabel;
}

void EntityAttributeWidget::setAnimal(weak_ptr<Animal> a)
{
   animal = a;
   update();
}

void EntityAttributeWidget::update()
{
    shared_ptr<Animal> sharedAnimal = animal.lock();
   if(!sharedAnimal)
   {
      defaultLabel->setVisible(true);
      healthLabel->setVisible(false);
      hungerLabel->setVisible(false);
      thirstLabel->setVisible(false);
      fearLabel->setVisible(false);
   }
   else
   {
      defaultLabel->setVisible(false);
      healthLabel->setVisible(true);
      hungerLabel->setVisible(true);
      thirstLabel->setVisible(true);
      fearLabel->setVisible(true);

      healthLabel->setText(healthText + QString::number(sharedAnimal->getHealth()));
      hungerLabel->setText(hungerText + QString::number(sharedAnimal->getHunger()));
      thirstLabel->setText(thirstText + QString::number(sharedAnimal->getThirst()));
      fearLabel->setText(fearText + QString::number(sharedAnimal->getFear()));
   }
}
