#include "Entity.h"

Entity::Entity(double x, double y, int radius, int creationDate) : Entity(Coordinate(x,y),radius,creationDate)
{
}

Entity::Entity(Coordinate c, int radius, int creationDate) : m_radius(radius), m_coordinate(c), m_creationDate(creationDate)
{
}

Entity::~Entity()
{

}

int Entity::play()
{
    return 0;
}
