#include "Coordinate.h"
#include "config.h"
#include <cmath>
#include <algorithm>

Coordinate::Coordinate(int x, int y)
{
    set(x,y);
}

void Coordinate::set(int x, int y)
{
    m_x = (x % WORLD_SIZE_X + WORLD_SIZE_X) % WORLD_SIZE_X; // x % y return a value btw -y + 1 and y - 1.
    m_y = (y % WORLD_SIZE_Y + WORLD_SIZE_Y) % WORLD_SIZE_Y; // x % y + y return a value btw 1 and 2y - 1
                                                            // (x % y + y) % y return a value btw 0 and y - 1
}

double Coordinate::getDistance(const Coordinate &c1, const Coordinate &c2)
{
    int deltaX = std::abs(c1.getX() - c2.getX());
    int deltaY = std::abs(c1.getY() - c2.getY());
    int deltaXTore = std::min(deltaX, WORLD_SIZE_X - deltaX);
    int deltaYTore = std::min(deltaY, WORLD_SIZE_Y - deltaY);
    return sqrt(deltaXTore * deltaXTore + deltaYTore * deltaYTore);
}

double Coordinate::getAngle(const Coordinate &c1, const Coordinate &c2)
{
    int x1 = c1.getX();
    int x2 = c2.getX();
    double deltaX = x2 - x1;
    int y1 = c1.getY();
    int y2 = c2.getY();
    double deltaY = y2 - y1;

    if (std::abs(x1 - x2) > WORLD_SIZE_X)
    {
        deltaX += (x1 < x2) ? -WORLD_SIZE_X : WORLD_SIZE_X;
    }

    if (std::abs(y1 - y2) > WORLD_SIZE_Y)
    {
        deltaY += (y1 < y2) ? -WORLD_SIZE_Y : WORLD_SIZE_Y;
    }

    if (deltaX == 0)
    {
        return (y2 > y1) ? PI/2.0 : -PI/2.0;
    }
    else if (deltaX > 0)
    {
        return std::atan(deltaY / deltaX);
    }
    else
    {
        return std::atan(deltaY / deltaX) + PI;
    }
}
