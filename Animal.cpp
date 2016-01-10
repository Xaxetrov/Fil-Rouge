#include "Animal.h"

Animal::Animal(int x, int y, int radius, int maxSpeed) : Solid(x, y, radius), m_maxSpeed(maxSpeed)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_fear = 0;
}

Animal::move(int speedPercentage)
{
	
}


