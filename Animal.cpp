#include "Animal.h"
#include <cmath>

Animal::Animal(int x, int y, int radius, int maxSpeed, World * world) : Solid(x, y, radius), m_maxSpeed(maxSpeed), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_fear = 0;
}

void Animal::move(int speedPercentage)
{
    setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
    if (!m_world->isCollision(*this))
    {
        setCoordinate(getX() + cos(m_angle + M_PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + M_PI) * speedPercentage * m_maxSpeed / 100);
    }
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
