#ifndef NONSOLID_H
#define NONSOLID_H

#include <mutex>
#include "Entity.h"

class NonSolid : public Entity
{
public:
    NonSolid(double x, double y, double radius);
    NonSolid(Coordinate c, double radius);

    virtual int play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList);

    bool isLiving() { return false; } // Temporary
};

#endif // NONSOLID_H
