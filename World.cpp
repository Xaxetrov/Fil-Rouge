#include "World.h"

World::World()
{
    //comment test
}

std::vector<Entity> & World::getEntities()
{
    return m_entities;
}

Coordinate & World::getSize()
{
    return m_size;
}

int World::getSizeX()
{
    return m_size.getX();
}

int World::getSizeY()
{
    return m_size.getY();
}

bool World::isCollision(const Entity &e) const
{
    std::vector<Entity>::const_iterator itEntities;
    for (itEntities = m_entities.begin(); itEntities != m_entities.end(); itEntities++)
    {
        if(&e != &(*itEntities) && isCollision(e, (*itEntities)))
        {
            return true;
        }
    }
    return false;


}

// private methods

bool World::isCollision(const Entity &e1, const Entity &e2) const
{
    Coordinate c1 = e1.getCoordinate();
    Coordinate c2 = e2.getCoordinate();
    return(Coordinate::distance(c1, c2) < e1.getRadius() + e2.getRadius());
}
