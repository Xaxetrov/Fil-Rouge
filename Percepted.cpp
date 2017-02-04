#include "Percepted.h"

Percepted::Percepted(std::weak_ptr<Entity> entity, double distance, int maxRange) : m_entity(entity), m_distance(distance),
        m_maxVisionRange(maxRange)
{}

//Percepted::Percepted()
//{
//    m_entity = std::weak_ptr<Entity>(); //create an empty entity
//    m_distance = 0;
//}

void Percepted::set(std::weak_ptr<Entity> entity, double distance)
{
    m_entity = entity;
    m_distance = distance;
}
