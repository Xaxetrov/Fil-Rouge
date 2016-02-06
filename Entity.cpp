#include "Entity.h"

Entity::Entity(int x, int y, int radius) : m_coordinate(x, y), m_radius(radius)
{
    m_creationDate = 0;//init creationDate here
}

Entity::~Entity()
{

}
