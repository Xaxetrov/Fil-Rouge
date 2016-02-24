#include "EntityAttributeWidget.h"

EntityAttributeWidget::EntityAttributeWidget()
{
   animal = nullptr; // Avoid random crashes

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

void EntityAttributeWidget::setAnimal(Animal * a)
{
   animal = a;
   update();
}

void EntityAttributeWidget::update()
{
   if(animal == nullptr)
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

      healthLabel->setText(healthText + QString::number(animal->getHealth()));
      hungerLabel->setText(hungerText + QString::number(animal->getHunger()));
      thirstLabel->setText(thirstText + QString::number(animal->getThirst()));
      fearLabel->setText(fearText + QString::number(animal->getFear()));
   }
}
