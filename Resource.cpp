#include "Resource.h"

Resource::Resource(double x, double y, double radius, int quantity, int quantityEvolution) : NonSolid(x, y, radius),
    m_quantity(quantity), m_quantityEvolution(quantityEvolution)
{
    m_maxQuantity = m_quantity;
}

Resource::Resource(Coordinate c, double radius, int quantity, int quantityEvolution) : NonSolid(c, radius),
    m_quantity(quantity), m_quantityEvolution(quantityEvolution)
{
    m_maxQuantity = m_quantity;
}

int Resource::getQuantity() const
{
    return m_quantity;
}

int Resource::getMaxQuantity() const
{
    return m_maxQuantity;
}

void Resource::setCurrantQuantity(int quantity)
{
    if(quantity < m_maxQuantity)
    {
        m_quantity = quantity;
    }
    else
    {
        m_quantity = m_maxQuantity;
    }
}

void Resource::setMaxQuantity(int maxQuantity)
{
    if(m_quantity > maxQuantity)
    {
        m_quantity = maxQuantity;
    }
    m_maxQuantity = maxQuantity;
}

int Resource::play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList)
{
    m_quantity += std::min(m_quantityEvolution,m_maxQuantity-m_quantity);
    return 0;
}
