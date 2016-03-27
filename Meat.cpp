#include "Meat.h"

Meat::Meat(int x, int y, int radius, int quantity) : Resource(x, y, radius, quantity, EVOLUTION_MEAT)
{
}

void Meat::eat(int quantity)
{
    m_quantity -= quantity;
}
