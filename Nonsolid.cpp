#include "Nonsolid.h"

NonSolid::NonSolid(double x, double y, double radius) : Entity(x, y, radius)
{

}

NonSolid::NonSolid(Coordinate c, double radius) : Entity(c, radius)
{

}

int NonSolid::play(int id)
{
    return 0;
}
