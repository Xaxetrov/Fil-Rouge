#include "Animal.h"
#include "Water.h"
#include "Vegetal.h"
#include "World.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world) :
    Solid(x, y, radius), m_energy(energy), m_age(0), m_maxSpeed(maxSpeed), m_damage(damage), m_world(world)
{
    m_angle = 0; //initialize angle here
    m_hunger = 0;
    m_thirst = 0;
    m_speed = 0;
    m_health = config::MAX_HEALTH;
    dead = false;
    m_fear = 0;
    m_mating = config::MAX_MATING;
    m_vision = new Vision(*this, m_angle, world->getGridOfEntities());

    //Determine if Animal is female or not (1/2 chance)
    static std::mt19937 generator(random_device{}());
    bernoulli_distribution distribution(0.5);
    m_female = distribution(generator);

    vector<unsigned int> layerSizes;
    for(unsigned int i = 0; i < NB_LAYERS; i++)
    {
      layerSizes.push_back(LAYER_SIZES[i]);
    }
    m_brain = new NeuralNetwork(layerSizes);
    setCreationDate(world->getWorldAge());
}

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, bool sex) : Animal(x, y ,radius, maxSpeed, damage, energy, world)
{
    m_female = sex;
}

Animal::Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, NeuralNetwork * brain, unsigned int mating) :
    Animal(x,y,radius,maxSpeed,damage,energy,world)
{
    m_mating = mating;
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
    m_age++;

    m_energy += config::ENERGY_RECUP;
    if(m_energy > config::DEFAULT_ENERGY)
      m_energy = config::DEFAULT_ENERGY;

    if(m_health <= 0 || dead)
    {
      dead = true;
      return 0;// if dead no need to continue playing.
      //m_world->killEntity(this); // RIP
    }
    else
    {
      m_hunger++;
      m_thirst++;
    }

    if(m_hunger >= config::MAX_HUNGER)
    {
        m_health -= 10;
        m_hunger = config::MAX_HUNGER;
    }
    else if(m_hunger > config::MAX_HUNGER*3/4)
    {
        m_health--;
    }
    else if(m_hunger < 0)
    {
        m_hunger = 0;
    }

    if(m_thirst >= config::MAX_THIRST)
    {
        m_health -= 10;
        m_thirst = config::MAX_THIRST;
    }
    else if(m_thirst > config::MAX_THIRST*3/4)
    {
      m_health--;
    }
    else if(m_thirst < 0)
    {
        m_thirst = 0;
    }

    if(m_mating != config::MAX_MATING)
    {
      m_mating++;
    }

    // The animal looks around itself
    m_vision->see();

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
    /*if(m_speed > 0)
    {
      World::mutexCollisionList.lock();
      World::mutexGridOfEntities.lock();
      move();
      World::mutexCollisionList.unlock();
      World::mutexGridOfEntities.unlock();
    }
    else // calcul of collisionList hasn't been effectuated
    {
        m_world->updateListCollision(this->shared_from_this());
    }*/

    attack();
    eat();
    drink();
    mate();

    return 0;
}

void Animal::move()
{
    if(m_speedPercentage > 0)
    {
      m_speed = m_speedPercentage * m_maxSpeed / 100.0;
      if(m_speed * config::MOVE_ENERGY_LOSS > m_energy)
        m_speed = m_energy / config::MOVE_ENERGY_LOSS / 2;
      m_energy -= m_speed * config::MOVE_ENERGY_LOSS / 2;

      int oldX = getX();
      int oldY = getY();
      setCoordinate(getX() + cos(m_angle) * m_speed, getY() + sin(m_angle) * m_speed);
      m_world->updateGridOfEntities(this->shared_from_this(), oldX, oldY, getX(), getY());
    }
    m_world->updateListCollision(this->shared_from_this());

    //Colision disabled !!!
//    vector<weak_ptr<Entity>> animalCollisionList = getSubListSolidCollision();
//    if(animalCollisionList.size() != 0)
//    {

//        //setCoordinate(getX() - cos(m_angle)*m_speed, getY() - sin(m_angle)*m_speed);
//    }
}

//TODO: TO FINISH
void Animal::mappageInput()
{
    m_nnInputs.clear();
    m_nnInputs.push_back((double)m_hunger / (double)config::MAX_HUNGER);
    m_nnInputs.push_back((double)m_thirst / (double)config::MAX_THIRST);
    m_nnInputs.push_back((double)m_health / (double)config::MAX_HEALTH);
    m_nnInputs.push_back((double)m_mating / (double)config::MAX_MATING);
    vector<std::shared_ptr<Percepted> > percepted = m_vision->getPercepted();
    for(std::shared_ptr<Percepted> p:percepted)
    {
        shared_ptr<Entity> e = p->getEntity();
        if(e != nullptr)
        {
            m_nnInputs.push_back(p->getEntity()->getNeralNetworkId());
            m_nnInputs.push_back(p->getDistance() / (double)p->getVisionRange());
        }
        else //if nothing is percepted
        {
            m_nnInputs.push_back(0);
            m_nnInputs.push_back(1);//if nothing is seen the max distance is send
        }
    }
}

void Animal::mappageOutput()
{
#ifdef DEBUG
    if(m_nnOutputs.size() == 3)
    {
        std::cerr << "incorect number of nn outputs" << std::endl;
        exit(-1);
    }
#endif
    m_speedPercentage = m_nnOutputs[0]*7;
    m_rotation = m_nnOutputs[1]/5;
    m_fear = m_nnOutputs[2]*config::MAX_FEAR;
}

void Animal::turn(double angle)
{
  if(fabs(angle) * config::TURN_ENERGY_LOSS > m_energy)
    angle = m_energy / config::TURN_ENERGY_LOSS / 2;
  m_energy -= fabs(angle) * config::TURN_ENERGY_LOSS / 2;

  m_angle += angle;
  m_angle = Coordinate::modulo2PI(m_angle);
}


// The animal drink one time for each pool it is on
void Animal::drink()
{
    if(m_speed <= config::MAX_SPEED_TO_EAT)
    {
        vector<weak_ptr<Entity>> waterCollisionList = getSubListCollision(ID_WATER);
        for (weak_ptr<Entity> weakWater:waterCollisionList)
        {
            // remove element from the list with a lambda expression because weak_pointer doesn't have == operator
            /*m_collisionList.remove_if([weakWater](weak_ptr<Entity> p)
                                      { return !( p.owner_before(weakWater) || weakWater.owner_before(p) ); }
                                     );*/
            shared_ptr<Entity> waterEntity = weakWater.lock();
            if(waterEntity)
            {
                shared_ptr<Water> water;
                if(water = dynamic_pointer_cast<Water>(waterEntity))
                {
                   if(m_thirst > 0)
                   {
                       int quantity = std::min(100,(int)m_thirst); //don't drink more than needed (no negative thirst)
                       World::mutexDrink.lock();
                       m_thirst -= water->drink(quantity); //drink as much as possible on the water source
                       World::mutexDrink.unlock();
                   }
                }
            }
        }
    }
}

// The animal drink one time for each pool it is on
void Animal::eat()
{
    if(m_speed <= config::MAX_SPEED_TO_EAT)
    {
        vector<weak_ptr<Entity>> foodCollisionList = getSubListResourceCollision();
        for (weak_ptr<Entity> weakFood:foodCollisionList)
        {
            // remove element from the list with a lambda expression because weak_pointer doesn't have == operator
            /*m_collisionList.remove_if([weakFood](weak_ptr<Entity> p)
                                      { return !( p.owner_before(weakFood) || weakFood.owner_before(p) ); }
                                     );*/
            shared_ptr<Entity> foodEntity = weakFood.lock();
            if(foodEntity)
            {
                tryToEat(foodEntity);
            }
        }
    }
}

void Animal::tryToEat(std::shared_ptr<Entity> food)
{
    //yes animal are herbivore...
    if(shared_ptr<Vegetal> vegetal = dynamic_pointer_cast<Vegetal>(food))
    {
       if(m_hunger > 0)
       {
           int quantity = std::min(config::EAT_MAX_VEGETAL_QUANTITY,(unsigned)m_hunger);
           World::mutexVegetal.lock();
           m_hunger -= vegetal->eat(quantity);
           World::mutexVegetal.unlock();
       }
       //heal himself
       if(m_health < config::MAX_HEALTH && m_thirst < config::MAX_THIRST*3/4)
       {
           m_health += std::min(config::EAT_MAX_HEALING_VALUE,(unsigned)(config::MAX_HEALTH-m_health));
       }
    }
}

void Animal::mate()
{
   vector<weak_ptr<Entity>> animalCollisionList = getSubListCollision(this->getTypeId());
   for(weak_ptr<Entity> weakAnimal:animalCollisionList)
   {
      shared_ptr<Entity> animalEntity = weakAnimal.lock();
      if(animalEntity)
      {
           if(tryToMate(animalEntity)) //virtual -> try to mate in the good way
           {
               break;
           }
      }
   }
}

bool Animal::tryToMate(std::shared_ptr<Entity> animalEntity)
{
    if(shared_ptr<Animal> animalToMate = dynamic_pointer_cast<Animal>(animalEntity))
    {
       // this Animal is the female
       if(m_female && !animalToMate->isFemale())
       {
          if(m_mating == config::MAX_MATING && animalToMate->getMating() == config::MAX_MATING)
          {
              World::mutexMateList.lock();
              m_world->updateMateList(this, animalToMate);
              World::mutexMateList.unlock();
              //this->reproduce(animalToMate);
              return true;
          }
       }
    }
    return false;
}

void Animal::attack()
/**
 * attack the Animal which are not of the same type as himself
 * and if they are in front of him (angle defined in config.h)
 * The attack value is stored in m_damage.
*/
{
    vector<weak_ptr<Entity>> animalCollisionList = getSubListSolidCollision();
    for(weak_ptr<Entity> weakAnimal:animalCollisionList)
    {
       shared_ptr<Entity> animalEntity = weakAnimal.lock();
       if(animalEntity)
       {
           if(animalEntity->getTypeId() != this->getTypeId())
           {
               double angle = Coordinate::getAngle(this->getCoordinate(),animalEntity->getCoordinate())-m_angle;
               if(std::abs(angle)<=config::MAX_ATTACK_ANGLE)
               {
                    if(shared_ptr<Animal> a=dynamic_pointer_cast<Animal>(animalEntity))
                    {
                        World::mutexAttackList.lock();
                        m_world->updateAttackList(a, m_damage);
                        World::mutexAttackList.unlock();
                    }
               }
           }
       }
    }
}

void Animal::evolve(NeuralNetwork *bestNN)
// Modify the neuronal network of the animal closer to the best one
{
    NeuralNetwork* NN = evolveNN();
    std::vector<NeuronLayer> layers = NN->getL();
    std::vector<NeuronLayer> bestLayers = bestNN->getL();
    const unsigned int layersNum=layers.size();
    //for each layer
    for (unsigned int layer=0; layer<layersNum; layer++)
    {
        std::vector<Neuron> neurons = layers.at(layer).getN();
        std::vector<Neuron> bestNeurons = bestLayers.at(layer).getN();
        const unsigned int neuronsNum = neurons.size();

        //for each neuron
        for (unsigned int neuron=0; neuron<neuronsNum; neuron++)
        {
            const std::vector<double> weights = neurons.at(neuron).getWeights();
            const std::vector<double> bestWeights = bestNeurons.at(neuron).getWeights();
            std::vector<double> newWeights;
            //for each weight
            for(unsigned int w=0; w<weights.size(); w++)
            {   newWeights.push_back(weights.at(neuron)+(bestWeights.at(neuron)-weights.at(neuron))*0.1);
            }
            neurons.at(neuron).setWeights(newWeights);
        }
    }
}

void Animal::loseLive(unsigned liveToLose)
{
    m_health -= liveToLose;
}


void Animal::addEntityInListCollision(weak_ptr<Entity> e)
{
    m_collisionList.push_back(e);
}

void Animal::clearEntityListCollision()
{
    m_collisionList.clear();
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

vector<weak_ptr<Entity>> Animal::getSubListSolidCollision()
{
    vector<weak_ptr<Entity>> subListCollision;
    for(weak_ptr<Entity> weakEntity:m_collisionList)
    {
        shared_ptr<Entity> e = weakEntity.lock();
        if(e)//if lock worked
        {
            if(e->getTypeId() >= ID_ANIMAL)
            {
                subListCollision.push_back(e);
            }
        }
    }
    return subListCollision;
}

vector<weak_ptr<Entity>> Animal::getSubListResourceCollision()
{
    vector<weak_ptr<Entity>> subListCollision;
    for(weak_ptr<Entity> weakEntity:m_collisionList)
    {
        shared_ptr<Entity> e = weakEntity.lock();
        if(e)//if lock worked
        {
            if(e->getTypeId() < ID_ANIMAL)
            {
                subListCollision.push_back(e);
            }
        }
    }
    return subListCollision;
}

unsigned int Animal::getAge() const
{
    return m_age;
}

unsigned int Animal::getMaxSpeed() const
{
    return m_maxSpeed;
}

int Animal::getHealth() const
{
    return m_health;
}

unsigned int Animal::getHunger() const
{
    return m_hunger;
}

unsigned int Animal::getThirst() const
{
    return m_thirst;
}

int Animal::getFear() const
{
    return m_fear;
}

unsigned int Animal::getMating() const
{
   return m_mating;
}

unsigned int Animal::getEnergy() const
{
   return m_energy;
}

double Animal::getScore() const
{
    return m_score;
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

NeuralNetwork *Animal::evolveNN()
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

void Animal::setMating()
{
   m_mating = 0;
}

void Animal::setBrain(NeuralNetwork *newBrain)
{
    delete(m_brain);
    m_brain = newBrain;
}

void Animal::setSex(bool sex)
{
    m_female = sex;
}

int Animal::getCurrentCellX() const
{
    return getX() / m_world->getCellSizeX();
}

int Animal::getCurrentCellY() const
{
    return getY() / m_world->getCellSizeY();
}
