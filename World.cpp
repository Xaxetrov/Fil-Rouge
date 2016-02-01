#include "World.h"

World::World()
{
    //comment test
}

std::vector<Entity *> &World::getEntities()
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

bool World::isCollision(const Entity* e) const
{
    for( Entity* currantEntity : m_entities)
    {
        if( e!=currantEntity && isCollision(e, currantEntity))
        {
            return true;
        }
    }
    return false;
}

// private methods

bool World::isCollision(const Entity *e1, const Entity *e2) const
{
    Coordinate c1 = e1->getCoordinate();
    Coordinate c2 = e2->getCoordinate();
    return(Coordinate::distance(c1, c2) < (e1->getRadius()+e2->getRadius()) );
}
