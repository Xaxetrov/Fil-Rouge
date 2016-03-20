#include "EntityFrame.h"

EntityFrame::EntityFrame()
{
   entityView = new EntityViewWidget();
   entityAttribute = new EntityAttributeWidget();

   QVBoxLayout * layout = new QVBoxLayout();
   layout->addWidget(entityView);
   layout->addWidget(entityAttribute);

   this->setLayout(layout);
}

EntityFrame::~EntityFrame()
{
   delete entityView;
   delete entityAttribute;
}

void EntityFrame::setAnimal(weak_ptr<Animal> a)
{
   entityView->setAnimal(a);
   entityAttribute->setAnimal(a);
}

void EntityFrame::update()
{
   entityView->updateView();
   entityAttribute->update();
}

void EntityFrame::resizeEvent(QResizeEvent *e)
{
   
}
