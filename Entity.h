#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"

class Entity
{
public:
    Entity(int x, int y, int creationDate);
    Entity(const Entity & e); //to disable copy constructor
    Coordinate getCoordinate() const {return m_coordinate;}
    void setCoordinate(int x, int y) {m_coordinate.set(x, y);}
    int getX() const {return m_coordinate.getX();}
    int getY() const {return m_coordinate.getY();}
    int getRadius() const {return m_radius;}
    int getCreationDate() {return m_creationDate;}

    virtual bool isLiving() = 0; // Temporary

private:
    Coordinate m_coordinate;
    int m_radius;
    int m_creationDate;
};

#endif // ENTITY_H
