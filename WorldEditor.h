#ifndef WORLDEDITOR_H
#define WORLDEDITOR_H

#include <QGraphicsView>

#include <memory>

#include "Resource.h"
#include "WorldColors.h"

class WorldEditor : public QGraphicsView
{
    Q_OBJECT //enable slot and signal suport in this class

public:
    WorldEditor(std::list<std::shared_ptr<Resource>> *resourcesList=0);

    WorldColors & getColors() {return colors;}

    enum Tools {vegetal,meat,water};

    void setResourcesList(std::list<std::shared_ptr<Resource>> *resourcesList);

public slots:
    void updateScene();
    //event
    void resizeEvent(QResizeEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void onWorldSizeChanged();

    void setCurrantTool(WorldEditor::Tools tool) {currantTool=tool;}
    void setCurrantRadius(int radius) {currantRadius=radius;}
    void setCurrantMaxQuantity(int maxQuantity) {currantMaxQuantity=maxQuantity;}

signals:
    void sceneUpdated();

private:
    void drawBasicEntity(QPoint pos,double radius, QBrush brush, QPen pen);
    void drawEntity(const std::shared_ptr<Entity> entity);
    void addWithCurrantTool(QPointF pos);
    void tryToRemoveAt(QPointF pos);

private:
    std::list<std::shared_ptr<Resource>> *resources;

    QGraphicsScene* m_scene;
    WorldColors colors;

    Tools currantTool;
    int currantRadius;
    int currantMaxQuantity;
};

#endif // WORLDEDITOR_H
