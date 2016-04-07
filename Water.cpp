#include "Water.h"

Water::Water(int x, int y, int radius, int quantity) : Resource(x,y,radius, quantity, EVOLUTION_WATER)
{
  
}

void Water::drink(int quantity)
{
    m_quantity -= quantity;
}
