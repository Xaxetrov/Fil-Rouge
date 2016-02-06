#include "Animal.h"
#include "config.h"
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
    if (!m_world->isCollision(this))
    {
        setCoordinate(getX() + cos(m_angle + PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + PI) * speedPercentage * m_maxSpeed / 100);
    }
}

int Animal::getMaxSpeed() const
{
    return m_maxSpeed;
}

int Animal::getHealth() const
{
    return m_health;
}

int Animal::getHunger() const
{
    return m_hunger;
}

int Animal::getThirst() const
{
    return m_thirst;
}

int Animal::getFear() const
{
    return m_fear;
}

double Animal::getAngle() const
{
    return m_angle;
}
