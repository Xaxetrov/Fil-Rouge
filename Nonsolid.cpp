#include "Nonsolid.h"

NonSolid::NonSolid(int x, int y, int radius) : Entity(x, y, radius)
{

}

NonSolid::NonSolid(Coordinate c, int radius) : Entity(c, radius)
{

}

int NonSolid::play()
{
    return 0;
}
