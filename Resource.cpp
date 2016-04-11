#include "Resource.h"

Resource::Resource(int x, int y, int radius, int quantity, int quantityEvolution) : NonSolid(x, y, radius),
    m_quantity(quantity*radius*radius), m_quantityEvolution(quantityEvolution*radius*radius)
{

}

int Resource::getQuantity() const
{
    return m_quantity;
}

int Resource::play()
{
    m_quantity += m_quantityEvolution;
    return 0;
}
