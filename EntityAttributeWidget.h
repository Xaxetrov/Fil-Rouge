#ifndef ENTITY_ATTRIBUTE_WIDGET_H
#define ENTITY_ATTRIBUTE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>

#include "Animal.h"

class EntityAttributeWidget : public QWidget
{

public:
   EntityAttributeWidget();
   virtual ~EntityAttributeWidget();
   void setAnimal(Animal * a);
   void update();

protected:
   Animal * animal;

   QVBoxLayout * layout;
   QLabel * defaultLabel;

   const QString healthText = "Health: ";
   QLabel * healthLabel;

   const QString hungerText = "Hunger: ";
   QLabel * hungerLabel;

   const QString thirstText = "Thirst: ";
   QLabel * thirstLabel;

   const QString fearText = "Fear: ";
   QLabel * fearLabel;

};

#endif //ENTITY_ATTRIBUTE_WIDGET_H
