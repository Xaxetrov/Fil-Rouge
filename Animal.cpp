#include "Animal.h"

Animal::Animal(int x, int y, int radius, int maxSpeed) : Solid(x, y, radius), m_maxSpeed(maxSpeed)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_fear = 0;
}

int Animal::getMaxSpeed()
{
    return m_maxSpeed;
}

int Animal::getHealth()
{
    return m_health;
}

int Animal::getHunger()
{
    return m_hunger;
}

int Animal::getThirst()
{
    return m_thirst;
}

int Animal::getFear()
{
    return m_fear;
}

double Animal::getAngle()
{
    return m_angle;
}
