#ifndef NONSOLID_H
#define NONSOLID_H

#include "Entity.h"

class NonSolid : public Entity
{
public:
    NonSolid(int x, int y, int radius);

    virtual int play();

    bool isLiving() { return false; }; // Temporary
};

#endif // NONSOLID_H
