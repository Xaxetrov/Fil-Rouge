#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"

class Entity
{
public:
    Entity(int x, int y, int creationDate);
    Entity(const Entity & e); //to disable copy constructor
    Coordinate getCoordinate() {return m_coordinate;}
    void setCoordinate(int x, int y) {m_coordinate.set(x, y);}
    int getX() {return m_coordinate.getX();}
    int getY() {return m_coordinate.getY();}
    int getRadius() {return m_radius;}
    int getCreationDate() {return m_creationDate;}

private:
    Coordinate m_coordinate;
    int m_radius;
    int m_creationDate;

};

#endif // ENTITY_H
