#ifndef ENTITY_FRAME_H
#define ENTITY_FRAME_H

#include <QFrame>
#include <QVBoxLayout>

#include "EntityAttributeWidget.h"
#include "EntityViewWidget.h"
#include "Animal.h"

class EntityFrame : public QFrame
{
    Q_OBJECT //enable slot and signal support for this class

public:
    EntityFrame();
    ~EntityFrame();

public slots:
    void resizeEvent(QResizeEvent *e);
    void setAnimal(Animal *a);
    void update();

protected:
    EntityViewWidget * entityView;
    EntityAttributeWidget * entityAttribute;


};

#endif //ENTITY_FRAME_H
