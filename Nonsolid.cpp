#include "Nonsolid.h"

NonSolid::NonSolid(double x, double y, double radius) : Entity(x, y, radius)
{

}

NonSolid::NonSolid(Coordinate c, double radius) : Entity(c, radius)
{

}

int NonSolid::play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList)
{
    return 0;
}
