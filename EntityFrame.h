#ifndef ENTITY_FRAME_H
#define ENTITY_FRAME_H

#include <QFrame>
#include <QVBoxLayout>

#include "EntityAttributeWidget.h"
#include "NNViewWidget.h"
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
    void setAnimal(std::weak_ptr<Animal> a);
    void update();

protected:
    EntityViewWidget * entityView;
    EntityAttributeWidget * entityAttribute;
    NNViewWidget * nnView;


};

#endif //ENTITY_FRAME_H
