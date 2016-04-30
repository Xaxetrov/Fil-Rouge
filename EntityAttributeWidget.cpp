#include "EntityAttributeWidget.h"

EntityAttributeWidget::EntityAttributeWidget()
{
   //animal = weak_ptr<Animal>(); // Avoid random crashes

   defaultLabel = new QLabel("No entity selected");

   healthLabel = new QLabel();
   hungerLabel = new QLabel();
   thirstLabel = new QLabel();
   fearLabel = new QLabel();
   matingLabel = new QLabel();
   sexLabel = new QLabel();

   layout = new QVBoxLayout();
   layout->addWidget(defaultLabel);
   layout->addWidget(healthLabel);
   layout->addWidget(hungerLabel);
   layout->addWidget(thirstLabel);
   layout->addWidget(fearLabel);
   layout->addWidget(sexLabel);
   layout->addWidget(matingLabel);

   healthLabel->setVisible(false);
   hungerLabel->setVisible(false);
   thirstLabel->setVisible(false);
   fearLabel->setVisible(false);
   sexLabel->setVisible(false);
   matingLabel->setVisible(false);

   this->setLayout(layout);
}

EntityAttributeWidget::~EntityAttributeWidget()
{
   delete layout;
   delete defaultLabel;
   delete healthLabel;
   delete hungerLabel;
   delete thirstLabel;
   delete fearLabel;
   delete sexLabel;
   delete matingLabel;
}

void EntityAttributeWidget::setAnimal(std::weak_ptr<Animal> a)
{
   animal = a;
   update();
}

void EntityAttributeWidget::update()
{
    std::shared_ptr<Animal> sharedAnimal = animal.lock();
   if(!sharedAnimal)
   {
      defaultLabel->setVisible(true);
      healthLabel->setVisible(false);
      hungerLabel->setVisible(false);
      thirstLabel->setVisible(false);
      fearLabel->setVisible(false);
      matingLabel->setVisible(false);
      sexLabel->setVisible(false);
   }
   else
   {
      defaultLabel->setVisible(false);
      healthLabel->setVisible(true);
      hungerLabel->setVisible(true);
      thirstLabel->setVisible(true);
      fearLabel->setVisible(true);
      matingLabel->setVisible(true);
      sexLabel->setVisible(true);

      healthLabel->setText(healthText + QString::number(sharedAnimal->getHealth()));
      hungerLabel->setText(hungerText + QString::number(sharedAnimal->getHunger()));
      thirstLabel->setText(thirstText + QString::number(sharedAnimal->getThirst()));
      fearLabel->setText(fearText + QString::number(sharedAnimal->getFear()));
      sexLabel->setText(sexText + (sharedAnimal->isFemale() ? "Female" : "Male") );
      matingLabel->setText(matingText + QString::number(sharedAnimal->getMating()));
   }
}
