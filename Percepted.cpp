#include "Percepted.h"

Percepted::Percepted(Entity *entity, double distance) : m_entity(entity), m_distance(distance)
{}

Percepted::Percepted()
{}

void Percepted::set(Entity *entity, double distance)
{
    m_entity = entity;
    m_distance = distance;
}
