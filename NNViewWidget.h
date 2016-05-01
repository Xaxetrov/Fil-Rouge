#ifndef NN_VIEW_WIDGET_H
#define NN_VIEW_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "Animal.h"
#include "WorldColors.h"


class NNViewWidget : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    NNViewWidget(std::weak_ptr<Animal> a = std::weak_ptr<Animal>());
    void setAnimal(std::weak_ptr<Animal> a);

    void resizeEvent(QResizeEvent *e);

public slots:
    void updateView();

private:
    std::weak_ptr<Animal> animal;
    QGraphicsScene scene;
    WorldColors colors;
};

#endif // NN_VIEW_WIDGET_H
