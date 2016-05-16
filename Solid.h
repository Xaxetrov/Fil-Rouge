#ifndef SOLID_H
#define SOLID_H

#include <mutex>
#include "Entity.h"

class Solid : public Entity
{
public:
    Solid(int x, int y, int radius, int creationDate=0);
    virtual int play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList);

};

#endif // SOLID_H
