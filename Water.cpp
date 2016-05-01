#include "Water.h"

Water::Water(double x, double y, double radius, double quantity) : Resource(x,y,radius, quantity, EVOLUTION_WATER)
{
  
}

int Water::drink(int quantity)
{
    int drinked = std::min(quantity,m_quantity);
    m_quantity -= drinked;
    return drinked;
}
