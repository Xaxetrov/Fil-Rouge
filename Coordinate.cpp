#include "Coordinate.h"

Coordinate::Coordinate(int x, int y) : m_x(x), m_y(y)
{

}

void Coordinate::set(int x, int y)
{
    setX(x);
    setY(y);
}
