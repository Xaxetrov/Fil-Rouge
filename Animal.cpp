#include "Animal.h"
#include "Water.h"
#include <iostream>
#include <iomanip>

using namespace std;

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, World * world) :
    Solid(x, y, radius), m_maxSpeed(maxSpeed), m_damage(damage), m_world(world)
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
    delete m_collisionList;
}

int Animal::play()
{
    if(m_health == 0 || dead)
    {
      dead = true;
      //m_world->killEntity(this); // RIP
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
    else if(m_hunger < 25 || m_thirst < 25)
    {
      m_health--;
    }
    else if(m_hunger < 50 || m_thirst < 50)
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
        inputs.push_back((double) percepted[i]->getEntity()->getTypeId());
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
    else // calcul of collisionList hasn't been effectuated
    {
        m_world->updateListCollision(this);
    }

    //eat();
    drink();

    return 0;
}

void Animal::move(int speedPercentage)
{

    setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
    m_world->updateListCollision(this);
    vector<Entity*> * animalCollisionList = getSubListCollision(ID_ANIMAL);
    if(animalCollisionList->size() != 0)
    {
        setCoordinate(getX() + cos(m_angle + PI) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle + PI) * speedPercentage * m_maxSpeed / 100);
        //setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
    }
    delete animalCollisionList;

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

int Animal::computeScore()
{
    return m_health*100 + m_hunger*10 + m_thirst*10 + m_fear*3;
}

void Animal::turn(double angle)
{
  m_angle += angle;
  m_angle = Coordinate::modulo2PI(m_angle);
}

// The animal drink one time for each pool it is on
void Animal::drink()
{
    vector<Entity*> * waterCollisionList = getSubListCollision(ID_WATER);
    vector<Entity*>::iterator itWaterCollisionList;
    for (itWaterCollisionList = waterCollisionList->begin(); itWaterCollisionList != waterCollisionList->end(); itWaterCollisionList++)
    {
        (dynamic_cast <Water*> (*itWaterCollisionList))->drink(2);
        m_thirst += 2;
    }
    delete waterCollisionList;
}

void Animal::addEntityInListCollision(Entity *e)
{
    m_collisionList->push_back(e);
}

vector<Entity*> * Animal::getSubListCollision(unsigned int idEntity)
{
    vector<Entity*> * subListCollision = new vector<Entity*>();
    vector<Entity*>::iterator itCollisionList;
    for (itCollisionList = m_collisionList->begin(); itCollisionList != m_collisionList->end(); itCollisionList++)
    {
        if((*itCollisionList)->getTypeId() == idEntity)
        {
            subListCollision->push_back(*itCollisionList);
        }
    }
    return subListCollision;
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

double Animal::getDamage() const
{
    return m_damage;
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
