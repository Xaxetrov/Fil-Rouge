#include "EntityFrame.h"

EntityFrame::EntityFrame()
{
   entityView = new EntityViewWidget();
   entityAttribute = new EntityAttributeWidget();
   nnView = new NNViewWidget();

   QVBoxLayout * layout = new QVBoxLayout();
   layout->addWidget(entityView);
   layout->addWidget(nnView);
   layout->addWidget(entityAttribute);

   this->setLayout(layout);
}

EntityFrame::~EntityFrame()
{
   delete entityView;
   delete nnView;
   delete entityAttribute;
}

void EntityFrame::setAnimal(weak_ptr<Animal> a)
{
   entityView->setAnimal(a);
   nnView->setAnimal(a);
   entityAttribute->setAnimal(a);
}

void EntityFrame::update()
{
   entityView->updateView();
   nnView->updateView();
   entityAttribute->update();
}

void EntityFrame::resizeEvent(QResizeEvent *e)
{

}
