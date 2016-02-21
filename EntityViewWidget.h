#ifndef ENTITYVIEWWIDGET_H
#define ENTITYVIEWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "Animal.h"
#include "WorldColors.h"


class EntityViewWidget : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    EntityViewWidget(Animal * a = nullptr);

public slots:
    void updateView();
    void resizeEvent(QResizeEvent *e);
    void setAnimal(Animal *a);

private:
    QPolygonF generateVisionSector(int angle1, int angle2, int depth, int numberOfPoint=3) const;

private:
    Animal * animal;
    QGraphicsScene scene;
    WorldColors colors;
};

#endif // ENTITYVIEWWIDGET_H
