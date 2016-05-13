#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <memory>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>

#include "WorldColors.h"
#include "World.h"
#include "Entity.h"
#include "Animal.h"

class WorldWidget : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    WorldWidget(World * world = 0);
    virtual ~WorldWidget();

    void updateTimerInterval();

    WorldColors & getColors();

    void setWorld(World * world);

    bool isSimulationRunning() const;

public slots:
    void updateScene();
    //event
    void resizeEvent(QResizeEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void selectAnimal(std::weak_ptr<Animal> a);
    void tick();
    void startSimulation(); //to start the timer
    void suspendSimulation(); //to stop the timer

signals:
    void animalSelected(std::weak_ptr<Animal> a);
    void sceneUpdated();

private:
    void drawEntity(const std::shared_ptr<Entity> entity);
    void drawAnimal(QPoint pos,double radius, double angle, QBrush brush, QPen pen);
    void drawAnimal(const std::shared_ptr<Animal> animal);
    void drawAnimal(const std::shared_ptr<Animal> animal, QPoint pos);
    void drawBasicEntity(QPoint pos,double radius, QBrush brush, QPen pen);

private:
    QGraphicsScene * m_scene;
    WorldColors colors;
    World * m_world;
    std::weak_ptr<Animal> selectedAnimal;
    //timer
    QTimer timer;

public: //Public const:
    //static const int UNIT_SIZE = 10;
};

#endif // WORLDWIDGET_H
