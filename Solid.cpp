#include "Solid.h"

Solid::Solid(int x, int y, int radius, int creationDate) : Entity(x, y, radius, creationDate)
{

}

int Solid::play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList)
{
    return 0;
}
