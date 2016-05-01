#ifndef NONSOLID_H
#define NONSOLID_H

#include "Entity.h"

class NonSolid : public Entity
{
public:
    NonSolid(double x, double y, double radius);
    NonSolid(Coordinate c, double radius);

    virtual int play();

    bool isLiving() { return false; } // Temporary
};

#endif // NONSOLID_H
