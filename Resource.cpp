#include "Resource.h"

Resource::Resource(int x, int y, int radius, int quantity, int quantityEvolution) : NonSolid(x, y, radius),
    m_quantity(quantity), m_quantityEvolution(quantityEvolution)
{

}

int Resource::getQuantity() const
{
    return m_quantity;
}

int Resource::play()
{
    m_quantity += m_quantityEvolution;
}
