#ifndef COORDINATE_H
#define COORDINATE_H

#include "config/config.h"
#include "config/errors.h"

#include <iostream>

class Coordinate
{
public:
    Coordinate(double x=0, double y=0);
    double getX() const {return m_x;}
    double getY() const {return m_y;}
    void set(double x, double y);

    static double getDistance(const Coordinate &c1, const Coordinate &c2);

    // Give the angle ((0, x), (c1, c2)) in rad
    // if c1 == c2, the angle is -PI/2
    static double getAngle(const Coordinate &c1, const Coordinate &c2);

private:
    double m_x;
    double m_y;
};

#endif // COORDINATE_H
