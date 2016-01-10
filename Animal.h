#ifndef ANIMAL_H
#define ANIMAL_H

#include "Solid.h"

class Animal : public Solid
{
public:
    Animal(int x, int y, int radius, int maxSpeed);

    int getMaxSpeed();
    int getHealth();
    int getHunger();
    int getThirst();
    int getFear();
    double getAngle();

    void die();
    void move(int speedPercentage);
    void turn(int angle);

private :
    int m_maxSpeed;
    double m_angle;
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    int m_brain; // change to neural net
    int m_vision; // change to AnimalVision

};

#endif // ANIMAL_H
