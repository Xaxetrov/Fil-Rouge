#include "WorldWidget.h"
#include "Animal.h"

WorldWidget::WorldWidget(World *world) : QGraphicsView(), m_world(world)
{
    m_scene = new QGraphicsScene();
    setScene(m_scene);
    updateScene();
}

WorldWidget::~WorldWidget()
{
    delete m_scene;
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
    QRect baseSquare(e->getX()-UNIT_SIZE/2,e->getY()-UNIT_SIZE/2,UNIT_SIZE,UNIT_SIZE);
    m_scene->addEllipse(baseSquare,colors.getEntityPen(e),colors.getEntityBrush(e));
    //TODO found why Animal and Entity are not polymorphic... (virtual method ?)
    /*if(Animal* living = dynamic_cast<Animal*>(e))
    {
        //add an eye to show the looking direction
        double angle = living->getAngle();
        int eyeX = e->getX()+cos(angle)*UNIT_SIZE/4;
        int eyeY = e->getX()+sin(angle)*UNIT_SIZE/4;
        QRect eyeSquare(eyeX,eyeY,UNIT_SIZE/2,UNIT_SIZE/2);
        m_scene->addEllipse(eyeSquare,colors.getEntityPen(*e),colors.getTeamsEyeBrush());
    }*/
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
