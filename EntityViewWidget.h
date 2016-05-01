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
    EntityViewWidget(std::weak_ptr<Animal> a = std::weak_ptr<Animal>());
    void setAnimal(std::weak_ptr<Animal> a);

    void resizeEvent(QResizeEvent *e);

public slots:
    void updateView();

private:
    QPolygonF generateVisionSector(double angle1, double angle2, int depth, int numberOfPoint=3) const;

private:
    std::weak_ptr<Animal> animal;
    QGraphicsScene scene;
    WorldColors colors;
};

#endif // ENTITYVIEWWIDGET_H
