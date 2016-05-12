#include "Vegetal.h"

Vegetal::Vegetal(double x, double y, double radius, int quantity) : Resource(x, y, radius, quantity, config::EVOLUTION_VEGETAL)
{
}

int Vegetal::eat(int quantity)
{
    int eated = std::min(quantity,m_quantity);
    m_quantity -= eated;
    return eated;
}
