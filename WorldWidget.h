#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include "QGraphicsView"
#include "QGraphicsScene"

#include "WorldColors.h"
#include "World.h"
#include "Entity.h"

class WorldWidget : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    WorldWidget(World * world);
    virtual ~WorldWidget();

    WorldColors & getColors();

public slots:
    void updateScene();

private:
    void drawEntity(const Entity &entity);

private:
    QGraphicsScene * m_scene;
    WorldColors colors;
    World * m_world;

public: //Public const:
    static const int UNIT_SIZE = 10;
};

#endif // WORLDWIDGET_H
