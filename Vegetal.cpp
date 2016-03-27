#include "Vegetal.h"

Vegetal::Vegetal(int x, int y, int radius, int quantity) : Resource(x, y, radius, quantity, EVOLUTION_VEGETAL)
{
}

void Vegetal::eat(int quantity)
{
    m_quantity -= quantity;
}
