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
