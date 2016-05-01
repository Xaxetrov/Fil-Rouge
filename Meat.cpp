#include "Meat.h"

Meat::Meat(double x, double y, double radius, int quantity) : Resource(x, y, radius, quantity, EVOLUTION_MEAT)
{
}

Meat::Meat(Coordinate c, double radius, int quantity) : Resource(c,radius,quantity, EVOLUTION_MEAT)
{
}

int Meat::eat(int quantity)
{
    int eated = std::min(quantity,m_quantity);
    m_quantity -= eated;
    return eated;
}
