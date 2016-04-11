#include "Meat.h"

Meat::Meat(int x, int y, int radius, int quantity) : Resource(x, y, radius, quantity, EVOLUTION_MEAT)
{
}

int Meat::eat(int quantity)
{
    int eated = std::min(quantity,m_quantity);
    m_quantity -= eated;
    return eated;
}
