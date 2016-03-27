#ifndef RESOURCE_H
#define RESOURCE_H

#include "NonSolid.h"

class Resource : public NonSolid
{
public:
    Resource(int x, int y, int radius, int quantity, int quantityEvolution);
    int play();

      int getQuantity() const;

protected :
    int m_quantity;
    int m_quantityEvolution;
};

#endif // RESOURCE_H
