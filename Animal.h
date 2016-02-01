#ifndef ANIMAL_H
#define ANIMAL_H

#include "Solid.h"
#include "World.h"

class Animal : public Solid
{
public:
    Animal(int x, int y, int radius, int maxSpeed, World * world);

    int getMaxSpeed();
    int getHealth();
    int getHunger();
    int getThirst();
    int getFear();
    double getAngle();

    void die();
    void move(int speedPercentage);
    void turn(double angle);

    bool isLiving() { return true; } // Temporary

private :
    int m_maxSpeed;
    double m_angle; // m_angle in rad
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    int m_brain; // change to neural net
    int m_vision; // change to AnimalVision
    World * m_world;

};

#endif // ANIMAL_H
