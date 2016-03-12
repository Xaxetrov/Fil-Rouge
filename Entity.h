#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"

/*
 * A Entity is something, anything
 */
class Entity
{
public:
    //ctor, dtor
    Entity(int x, int y, int creationDate);
    Entity(const Entity & e); //to disable copy constructor
    virtual ~Entity();

    //attributes accessors
    const Coordinate * getCoordinate() const {return &m_coordinate;}
    void setCoordinate(double x, double y) {m_coordinate.set(x, y);}
    double getX() const {return m_coordinate.getX();}
    double getY() const {return m_coordinate.getY();}
    double getRadius() const {return m_radius;}
    int getCreationDate() {return m_creationDate;}

    virtual int play();
    virtual unsigned int getTypeId() = 0; //?

private:
    Coordinate m_coordinate;
    int m_radius;
    int m_creationDate;
};

#endif // ENTITY_H
