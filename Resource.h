#ifndef RESOURCE_H
#define RESOURCE_H

#include "Nonsolid.h"

class Resource : public NonSolid
{
public:
    Resource(int x, int y, int radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    Resource(Coordinate c, int radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    int play();

    int getQuantity() const;
    virtual bool isDead() const{return false;} //I'm unkillable !!!

protected :
    int m_quantity;
    int m_quantityEvolution;
};

#endif // RESOURCE_H
