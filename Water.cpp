#include "Water.h"

Water::Water(int x, int y, int radius, int quantity) : Resource(x,y,radius, quantity, EVOLUTION_WATER)
{
  
}

int Water::drink(int quantity)
{
    int drinked = std::min(quantity,m_quantity);
    m_quantity -= drinked;
    return drinked;
}
