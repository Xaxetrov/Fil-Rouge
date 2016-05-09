#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

#include <memory>

#include "Resource.h"
#include "WorldColors.h"

class WorldEditor : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    WorldEditor(std::vector<std::shared_ptr<Resource>> *resourcesList);

    WorldColors & getColors() {return colors;}

    enum Tools {vegetal,meat,water};

    void setCurrantTool(Tools tool) {currantTool=tool;}
    void setCurrantRadius(int radius) {curantRadius=radius;}
    void setCurrantMaxQuantity(int maxQuantity) {curantMaxQuantity=maxQuantity;}

public slots:
    void updateScene();
    //event
    void resizeEvent(QResizeEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void sceneUpdated();

private:
    void drawBasicEntity(QPoint pos,double radius, QBrush brush, QPen pen);
    void drawEntity(const std::shared_ptr<Entity> entity);
    void addWithCurrantTool(QPointF pos);
    void tryToRemoveAt(QpointF pos);

private:
    std::vector<std::shared_ptr<Resource>> *resources;

    QGraphicsScene m_scene;
    WorldColors colors;

    Tools currantTool;
    int curantRadius;
    int curantMaxQuantity;
};

#endif // WORLDEDITOR_H
