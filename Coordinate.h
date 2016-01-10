#ifndef COORDINATE_H
#define COORDINATE_H


class Coordinate
{
public:
    Coordinate(int x=0, int y=0);
    int getX() {return m_x;}
    int getY() {return m_y;}
    void setX(int x);
    void setY(int y);
    void set(int x, int y);

private:
    int m_x;
    int m_y;
};

#endif // COORDINATE_H
