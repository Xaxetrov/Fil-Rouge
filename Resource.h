#ifndef RESOURCE_H
#define RESOURCE_H

#include <mutex>
#include "Nonsolid.h"

/*
 * A resource is an entity which will be consumed by other entities
 */
class Resource : public NonSolid
{
public:
    //ctors, dtors
    Resource(double x, double y, double radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    Resource(Coordinate c, double radius, int quantityPerUnit, int quantityEvolutionPerUnit);

    //getters
    int getQuantity() const;
    int getMaxQuantity() const;
    virtual bool isDead() const{return false;} //I'm unkillable !!!

    //setters
    void setCurrantQuantity(int quantity);
    void setMaxQuantity(int maxQuantity);

    //game methods
    int play(int id);
    /*
     * for now, a resource does nothing on its turn
     */

protected :
    int m_quantity;
    int m_quantityEvolution;
    int m_maxQuantity;
};

#endif // RESOURCE_H
