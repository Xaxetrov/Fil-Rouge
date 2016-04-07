#include "Animal.h"
#include "Water.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>

using namespace std;

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, World * world) :
    Solid(x, y, radius), m_maxSpeed(maxSpeed), m_damage(damage), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_health = MAX_HEALTH;
    dead = false;
    m_fear = 0;
    m_mating = MAX_MATING;
    m_vision = new Vision(getCoordinate(), m_angle, world->getEntities());

    //Determine if Animal is female or not (1/2 chance)
    default_random_engine generator(random_device{}());
    bernoulli_distribution distribution(0.5);
    m_female = distribution(generator);

    vector<unsigned int> layerSizes;
    for(unsigned int i = 0; i < NB_LAYERS; i++)
    {
      layerSizes.push_back(LAYER_SIZES[i]);
    }
    m_brain = new NeuralNetwork(layerSizes);
}

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, World * world, bool sex) : Animal(x, y ,radius, maxSpeed, damage, world)
{
    m_female = sex;
}

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, World * world, NeuralNetwork * brain, int mating) :
    Solid(x, y, radius), m_maxSpeed(maxSpeed), m_damage(damage), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_health = MAX_HEALTH;
    dead = false;
    m_fear = 0;
    m_mating = mating;
    m_vision = new Vision(getCoordinate(), m_angle, world->getEntities());

    //Determine if Animal is female or not (1/2 chance)
    /*default_random_engine generator(random_device{}());
    bernoulli_distribution distribution(0.5);
    m_female = distribution(generator);*/

    m_brain = brain;

}

Animal::~Animal()
{
    delete(m_vision);
    delete(m_brain);
    //delete m_collisionList;
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
      m_hunger++;
      m_thirst++;
    }

    if(m_hunger == MAX_HUNGER || m_thirst == MAX_THIRST)
    {
      dead = true;
    }
    else if(m_hunger > 50 || m_thirst > 50)
    {
      m_health--;
    }

    if(m_mating != MAX_MATING)
    {
      m_mating++;
    }

    // Inputs and outputs of the neural network
    vector<double> inputs;
    vector<double> outputs;

    // The animal looks around itself
    m_vision->see();
    /*vector<const Percepted*> percepted = m_vision->getPercepted();

    for(unsigned int i = 0; i < percepted.size(); i++)
    {
      if(percepted[i]->getEntity() != nullptr) // If it sees something
      {
        inputs.push_back((double) percepted[i]->getEntity()->getTypeId());
        inputs.push_back(percepted[i]->getDistance());

        // Test for the collision
        // inputs.push_back(0.0);
        // inputs.push_back(0.0);
      }
      else
      {
        inputs.push_back(0.0);
        inputs.push_back(0.0);
      }
    }*/

    // get mapping of inputs
    mappageInput();
    // The animal decides what to do
    m_nnOutputs = m_brain->run(m_nnInputs);
    // get mapping of outputs
    mappageOutput();

    // The animal moves
    // First it turns, then it moves
    if(m_rotation != 0)
    {
      turn(m_rotation);
    }
    if(m_speed > 0)
    {
      move(m_speed);
    }
    else // calcul of collisionList hasn't been effectuated
    {
        m_world->updateListCollision(this->shared_from_this());
    }

    //eat();
    drink();
    //mate();

    return 0;
}

void Animal::move(int speedPercentage)
{
    double speed = speedPercentage * m_maxSpeed / 100.0;
    setCoordinate(getX() + cos(m_angle) * speed, getY() + sin(m_angle) * speed);
    m_world->updateListCollision(this->shared_from_this());
    vector<weak_ptr<Entity>> animalCollisionList = getSubListCollision(ID_ANIMAL);// Warning -> Animal != Solid
    if(animalCollisionList.size() != 0)
    {
        setCoordinate(getX() - cos(m_angle)*speed, getY() - sin(m_angle)*speed);
        //setCoordinate(getX() + cos(m_angle) * speedPercentage * m_maxSpeed / 100, getY() + sin(m_angle) * speedPercentage * m_maxSpeed / 100);
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

int Animal::computeScore()
{
    return m_health*100 + m_hunger*10 + m_thirst*10 + m_fear*3;
}

//TO FINISH
void Animal::mappageInput()
{
    m_nnInputs.clear();
    m_nnInputs.push_back(m_hunger);
    m_nnInputs.push_back(m_thirst);
    m_nnInputs.push_back(m_health);
    const vector<const Percepted*> & percepted = m_vision->getPercepted();
    for(const Percepted* p:percepted)
    {
        shared_ptr<Entity> e = p->getEntity();
        if(e != nullptr)
        {
            m_nnInputs.push_back(p->getEntity()->getTypeId());
            m_nnInputs.push_back(p->getDistance());
        }
        else //if nothing is percepted
        {
            m_nnInputs.push_back(0);
            m_nnInputs.push_back(100);
        }
    }
}

void Animal::mappageOutput()
{
    m_speed = m_nnOutputs[0];
    m_rotation = m_nnOutputs[1];
    m_fear = m_nnOutputs[2];
}

void Animal::turn(double angle)
{
  m_angle += angle;
  m_angle = Coordinate::modulo2PI(m_angle);
}


// The animal drink one time for each pool it is on
void Animal::drink()
{
    vector<weak_ptr<Entity>> waterCollisionList = getSubListCollision(ID_WATER);
    for (weak_ptr<Entity> weakWater:waterCollisionList)
    {
        // remove element from the list with a lambda expression because weak_pointer doesn't have == operator
        m_collisionList.remove_if([weakWater](weak_ptr<Entity> p)
                                  { return !( p.owner_before(weakWater) || weakWater.owner_before(p) ); }
                                 );
        shared_ptr<Entity> waterEntity = weakWater.lock();
        if(waterEntity)
        {
            shared_ptr<Water> water;
            if(water = dynamic_pointer_cast<Water>(waterEntity))
            {
               if(m_thirst > 0)
               {
                  water->drink(2);
                  m_thirst -= 2;
               }
            }
        }
    }
}

void Animal::mate()
{
   vector<weak_ptr<Entity>> animalCollisionList = getSubListCollision(ID_ANIMAL);
   for(weak_ptr<Entity> weakAnimal:animalCollisionList)
   {
      m_collisionList.remove_if([weakAnimal](weak_ptr<Entity> p)
                                { return !( p.owner_before(weakAnimal) || weakAnimal.owner_before(p) ); }
                               );
      shared_ptr<Entity> animalEntity = weakAnimal.lock();
      if(animalEntity)
      {
         shared_ptr<Animal> animalToMate;
         if(animalToMate = dynamic_pointer_cast<Animal>(animalEntity))
         {
            // this Animal is the female
            if(m_female && !animalToMate->isFemale())
            {
               if(m_mating == MAX_MATING && animalToMate->getMating() == MAX_MATING)
               {
                  this->reproduce(animalToMate);
                  break;
               }
            }
         }
      }
   }
}

void Animal::reproduce(shared_ptr<Animal> father)
{
    // Use a normal distribution to determine the number of children of litter
    default_random_engine generator(random_device{}());
    normal_distribution<double> distribution(MAX_CHILD_PER_ANIMAL/2, 1.5);
    int numberChild = (int)distribution(generator);

    // Normalize in the possible range
    if(numberChild < 0) numberChild = 0;
    else if(numberChild > MAX_CHILD_PER_ANIMAL) numberChild = MAX_CHILD_PER_ANIMAL;

    // Create the new entity around the mother (in a circle)
    int child = 0;
    double angleIntervalle = (2*PI)/(double)numberChild;
    double baseAngle = 0;
    double baseRadius = 4*getRadius();

    while(child < numberChild)
    {
       NeuralNetwork * childBrain = new NeuralNetwork( *(father->getBrain()), *m_brain  );
        double distX = baseRadius*cos(baseAngle);
        double distY = baseRadius*sin(baseAngle);
        shared_ptr<Animal> animal(make_shared<Animal>(getX()+distX, getY()-distY, 10, 50, 2, m_world, childBrain) );
        m_world->addEntity(animal);
        baseAngle += angleIntervalle;
        child++;
    }
    m_mating = 0;
    father->setMating();
}

void Animal::addEntityInListCollision(weak_ptr<Entity> e)
{
    m_collisionList.push_back(e);
}

vector<weak_ptr<Entity>> Animal::getSubListCollision(unsigned int idEntity)
{
    vector<weak_ptr<Entity>> subListCollision;
    for(weak_ptr<Entity> weakEntity:m_collisionList)
    {
        shared_ptr<Entity> e = weakEntity.lock();
        if(e)//if lock worked
        {
            if(e->getTypeId() == idEntity)
            {
                subListCollision.push_back(e);
            }
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

int Animal::getMating() const
{
   return m_mating;
}

void Animal::setMating()
{
   m_mating = 0;
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

const NeuralNetwork * Animal::getBrain() const
{
   return m_brain;
}

bool Animal::isDead() const
{
   return dead;
}

bool Animal::isFemale() const
{
   return m_female;
}

double Animal::getSpeed() const
{
    return m_speed;
}

double Animal::getRotation() const
{
    return m_rotation;
}
