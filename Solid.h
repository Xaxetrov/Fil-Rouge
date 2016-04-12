#ifndef SOLID_H
#define SOLID_H

#include "Entity.h"

class Solid : public Entity
{
public:
    Solid(int x, int y, int radius, int creationDate=0);
    virtual int play();

};

#endif // SOLID_H
