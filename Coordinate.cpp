#include "Coordinate.h"
#include "config.h"
#include <cmath>
#include <algorithm>

Coordinate::Coordinate(int x, int y) : m_x(x), m_y(y)
{

}

void Coordinate::set(int x, int y)
{
    m_x = (x % WORLD_SIZE_X + WORLD_SIZE_X) % WORLD_SIZE_X; // x % y return a value btw -y + 1 and y - 1.
    m_y = (y % WORLD_SIZE_Y + WORLD_SIZE_Y) % WORLD_SIZE_Y; // x % y + y return a value btw 1 and 2y - 1
                                                            // (x % y + y) % y return a value btw 0 and y - 1
}

double Coordinate::distance(const Coordinate &c1, const Coordinate &c2)
{
    int deltaX = std::min(c1.getX() - c2.getX(), WORLD_SIZE_X - c1.getX() + c2.getX());
    int deltaY = std::min(c1.getY() - c2.getY(), WORLD_SIZE_Y - c1.getY() + c2.getY());
    return sqrt(deltaX * deltaX + deltaY * deltaY);
}
