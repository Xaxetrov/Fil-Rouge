#include "World.h"
#include "config.h"

World::World()
{
    m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
}

std::vector<Entity *> &World::getEntities()
{
    return m_entities;
}

Coordinate & World::getSize()
{
    return m_size;
}

int World::getSizeX() const
{
    return m_size.getX();
}

int World::getSizeY() const
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

void World::addEntity(Entity *entity)
{
    m_entities.push_back(entity);
}

// private methods

bool World::isCollision(const Entity *e1, const Entity *e2) const
{
    Coordinate c1 = e1->getCoordinate();
    Coordinate c2 = e2->getCoordinate();
    return(Coordinate::getDistance(c1, c2) < (e1->getRadius()+e2->getRadius()) );
}
