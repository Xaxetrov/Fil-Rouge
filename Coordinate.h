#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
public:
    Coordinate(int x=0, int y=0);
    int getX() const {return m_x;}
    int getY() const {return m_y;}
    void set(int x, int y);

    static double getDistance(const Coordinate &c1, const Coordinate &c2);

    // Give the angle ((0, x), (c1, c2)) in rad
    // if c1 == c2, the angle is -PI/2
    static double getAngle(const Coordinate &c1, const Coordinate &c2);

private:
    int m_x;
    int m_y;
};

#endif // COORDINATE_H
