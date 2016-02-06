#include "WorldWidget.h"
#include "Animal.h"

WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
    m_scene = new QGraphicsScene();
    setScene(m_scene);
}

WorldWidget::~WorldWidget()
{
    delete m_scene;
}

void WorldWidget::setWorld(World *world)
{
    m_world = world;
}

void WorldWidget::updateScene()
{
    //clear the scene:
    m_scene->clear();
    m_scene->setSceneRect(0,0,m_world->getSizeX(),m_world->getSizeY());
    //add each entity to the scene one by one:
    std::vector<Entity*> & entities = m_world->getEntities();
    for(Entity* ite : entities)
    {
        drawEntity(ite);
    }
}

void WorldWidget::drawEntity(const Entity * e)
{
    //draw a circle representing the Entity
    QRect baseSquare(e->getX()-e->getRadius(),e->getY()-e->getRadius(),e->getRadius()*2,e->getRadius()*2);
    m_scene->addEllipse(baseSquare,colors.getEntityPen(e),colors.getEntityBrush(e));
    if(const Animal* const living = dynamic_cast<const Animal*>(e))
    {
        //add an eye to show the looking direction
        double angle = living->getAngle();
        int eyeRadius = e->getRadius()/3;
        int eyeXCenter = e->getX()+cos(angle)*(e->getRadius()-eyeRadius);
        int eyeYCenter = e->getX()+sin(angle)*(e->getRadius()-eyeRadius);
        QRect eyeSquare(eyeXCenter-eyeRadius,eyeYCenter-eyeRadius,eyeRadius*2,eyeRadius*2);
        m_scene->addEllipse(eyeSquare,colors.getEntityPen(e),colors.getTeamsEyeBrush());
    }
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
