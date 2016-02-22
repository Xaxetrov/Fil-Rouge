#include "Animal.h"
#include <fstream>
using namespace std;

Animal::Animal(int x, int y, int radius, int maxSpeed, World * world) : Solid(x, y, radius), m_maxSpeed(maxSpeed), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_fear = 0;
    m_vision = new Vision(getCoordinate(), m_angle, world->getEntities());

    vector<unsigned int> layerSizes;
    for(unsigned int i = 0; i < NB_LAYERS; i++)
    {
      layerSizes.push_back(LAYER_SIZES[i]);
    }
    m_brain = new NeuralNetwork(layerSizes);
}

Animal::~Animal()
{
    delete(m_vision);
    delete(m_brain);
}

int Animal::play()
{
    vector<double> inputs;
    vector<double> outputs;
    // TO DO : give values to inputs

    outputs = m_brain->run(inputs);

    if(outputs[0] > 0)
    {
      move(outputs[0]);
    }

    return 0;
}

void Animal::move(int speedPercentage)
{
    if (m_world->isCollision(this))
    {
        setCoordinate(getX() + cos(m_angle + PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + PI) * speedPercentage * m_maxSpeed / 100);
    }
    else
    {
      setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
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

const Vision * Animal::getVision() const
{
    return m_vision;
}
