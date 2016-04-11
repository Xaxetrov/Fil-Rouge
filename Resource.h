#ifndef RESOURCE_H
#define RESOURCE_H

#include "Nonsolid.h"

class Resource : public NonSolid
{
public:
    Resource(int x, int y, int radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    int play();

    int getQuantity() const;

protected :
    int m_quantity;
    int m_quantityEvolution;
};

#endif // RESOURCE_H
