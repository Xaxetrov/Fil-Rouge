#include "Entity.h"

Entity::Entity(double x, double y, int radius) : m_coordinate(x, y), m_radius(radius)
{
    m_creationDate = 0;//init creationDate here
}

Entity::~Entity()
{

}

int Entity::play()
{
    return 0;
}
