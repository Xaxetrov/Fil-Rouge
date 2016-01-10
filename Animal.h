#ifndef ANIMAL_H
#define ANIMAL_H

#include "Solid.h"
#include "World.h"

class Animal : public Solid
{
public:
    Animal(int x, int y, int radius, int maxSpeed, World * world);

    int getMaxSpeed() {return m_maxSpeed;}
    int getHealth() {return m_health;}
    int getHunger() {return m_hunger;}
    int getThirst() {return m_thirst;}
    int getFear() {return m_fear;}

    void die();
    void move(int speedPercentage);
    void turn(int angle);

private :
    int m_maxSpeed;
    int m_angle; // m_angle in rad
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    int m_brain; // change to neural net
    int m_vision; // change to AnimalVision
    World * m_world;

};

#endif // ANIMAL_H
