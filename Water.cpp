#include "Water.h"

Water::Water(int x, int y, int radius, int quantity) : NonSolid(x,y,radius), m_quantity(quantity)
{
  
}

int Water::getQuantity() const
{
    return m_quantity;
}

void Water::drink(int quantity)
{
    m_quantity -= quantity;
}

int Water::play()
{
    m_quantity++;
    return 0;
}
