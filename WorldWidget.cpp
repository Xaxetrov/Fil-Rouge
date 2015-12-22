#include "WorldWidget.h"

WorldWidget::WorldWidget()
{

}

void WorldWidget::updateView()
{
    //clear the scene:
    m_scene->clear();
    //add each entity to the scene one by one:
    std::vector<Entity> entities = m_world->getEntities();
    for(std::vector<Entity>::iterator ite=entities.begin() ; ite!=entities.end() ; ite++)
    {
        drawEntity(ite);
    }
}

void WorldWidget::drawEntity(Entity &e)
{
    QRect baseSquare(e.getX()-UNIT_SIZE/2,e.getY()-UNIT_SIZE/2,UNIT_SIZE,UNIT_SIZE);
    m_scene->addEllipse(baseSquare,colors.getEntityPen(e),colors.getEntityBrush(e));
}

WorldColors & WorldWidget::getColors()
{
    return colors;
}
