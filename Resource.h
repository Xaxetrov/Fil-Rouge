#ifndef RESOURCE_H
#define RESOURCE_H

#include <mutex>
#include "Nonsolid.h"

class Resource : public NonSolid
{
public:
    Resource(double x, double y, double radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    Resource(Coordinate c, double radius, int quantityPerUnit, int quantityEvolutionPerUnit);
    int play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList);

    int getQuantity() const;
    int getMaxQuantity() const;
    virtual bool isDead() const{return false;} //I'm unkillable !!!

    void setCurrantQuantity(int quantity);
    void setMaxQuantity(int maxQuantity);

protected :
    int m_quantity;
    int m_quantityEvolution;
    int m_maxQuantity;
};

#endif // RESOURCE_H
