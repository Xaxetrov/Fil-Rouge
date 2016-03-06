#include "Animal.h"
#include <iostream>
#include <iomanip>

Animal::Animal(int x, int y, int radius, int maxSpeed, World * world) : Solid(x, y, radius), m_maxSpeed(maxSpeed), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 100;
    m_thirst = 100;
    m_health = 100;
    dead = false;
    m_fear = 0;
    m_vision = new Vision(getCoordinate(), &m_angle, world->getEntities());

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
    if(m_health == 0 || dead)
    {
      dead = true;
    }
    else
    {
      m_hunger--;
      m_thirst--;
    }
    
    if(m_hunger == 0 || m_thirst == 0)
    {
      dead = true;
    }
    else if(m_hunger < 50 || m_thirst < 50)
    {
      m_health--;
    }
    else if(m_hunger < 25 || m_thirst < 25)
    {
      m_health--;
    }


    // Inputs and outputs of the neural network
    vector<double> inputs;
    vector<double> outputs;

    // The animal looks around itself
    m_vision->see();
    vector<const Percepted*> percepted = m_vision->getPercepted();

    for(unsigned int i = 0; i < percepted.size(); i++)
    {
      if(percepted[i]->getEntity() != nullptr) // If it sees something
      {
        inputs.push_back(/*(double) percepted[i]->getEntity()->getTypeId()*/0.0);
        inputs.push_back(percepted[i]->getDistance());
      }
      else
      {
        inputs.push_back(0.0);
        inputs.push_back(0.0);
      }
    }

    // The animal decides what to do
    outputs = m_brain->run(inputs);

    // The animal moves
    // First it turns, then it moves
    if(outputs[1] != 0)
    {
      turn(outputs[1]);
    }
    if(outputs[0] > 0)
    {
      move(outputs[0]);
    }

    return 0;
}

void Animal::move(int speedPercentage)
{
    if (speedPercentage != 5)
        std::cout << speedPercentage << std::endl;

    setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
    if (m_world->isCollision(this))
    {
        setCoordinate(getX() + cos(m_angle + PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + PI) * speedPercentage * m_maxSpeed / 100);
    }

//    if (m_world->isCollision(this))
//    {
//        setCoordinate(getX() + cos(m_angle + PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + PI) * speedPercentage * m_maxSpeed / 100);
//        //setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
//    }
//    else
//    {
//      setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
//    }
}

void Animal::turn(double angle)
{
  m_angle += angle;
  cout << setprecision(10) << m_angle << std::endl;
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

bool Animal::isDead() const
{
   return dead;
}
