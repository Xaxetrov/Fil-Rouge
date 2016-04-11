#include "Resource.h"

Resource::Resource(int x, int y, int radius, int quantity, int quantityEvolution) : NonSolid(x, y, radius),
    m_quantity(quantity), m_quantityEvolution(quantityEvolution)
{
    m_maxQuantity = m_quantity;
}

Resource::Resource(Coordinate c, int radius, int quantity, int quantityEvolution) : NonSolid(c, radius),
    m_quantity(quantity), m_quantityEvolution(quantityEvolution)
{
    m_maxQuantity = m_quantity;
}

int Resource::getQuantity() const
{
    return m_quantity;
}

int Resource::play()
{
    m_quantity += std::min(m_quantityEvolution,m_maxQuantity-m_quantity);
    return 0;
}
