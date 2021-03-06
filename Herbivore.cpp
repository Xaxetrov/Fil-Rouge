#include "Herbivore.h"
#include "Vegetal.h"


Herbivore::Herbivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int maxMating, unsigned int generationNumber, World *world):
    Animal(x,y,maxSpeed,damage,energy,maxMating,generationNumber,world)
{
}
Herbivore::Herbivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int maxMating, unsigned int generationNumber, World *world, bool sex):
    Animal(x,y,maxSpeed,damage,energy,maxMating,generationNumber,world, sex)
{
}

Herbivore::Herbivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int maxMating, unsigned int generationNumber, World *world, NeuralNetwork * brain, int mating):
    Animal(x,y,maxSpeed,damage,energy,maxMating,generationNumber,world, brain, mating)
{
}


void Herbivore::tryToEat(std::shared_ptr<Entity> food)
{
    //Herbivore are... herbivore... so they try to eat vegetal
    if(std::shared_ptr<Vegetal> vegetal = std::dynamic_pointer_cast<Vegetal>(food))
    {
       if(m_hunger > 0)
       {
           int quantity = std::min(config::EAT_MAX_VEGETAL_QUANTITY,(unsigned)m_hunger);
           World::mutexVegetal.lock();
           double eatenQuantity = vegetal->eat(quantity);
           World::mutexVegetal.unlock();
           m_hunger -= eatenQuantity;
           //m_radius += config::FATNESS_HERBIVORE * eatenQuantity;
       }
       //heal himself
       if(m_health < config::MAX_HEALTH && m_thirst < config::MAX_THIRST*3/4)
       {
           m_health += std::min(config::EAT_MAX_HEALING_VALUE,(unsigned)(config::MAX_HEALTH-m_health));
       }
    }
}

bool Herbivore::tryToMate(std::shared_ptr<Entity> herbivoreEntity)
{
    if(std::shared_ptr<Herbivore> herbivoreToMate = std::dynamic_pointer_cast<Herbivore>(herbivoreEntity))
    {
       // this Animal is the female
       if(m_female && !herbivoreToMate->isFemale())
       {
            //both herbivore are ready to mate
          if(m_mating >= m_maxMating && herbivoreToMate->getMating() >= herbivoreToMate->getMaxMating())
          {
              //this herbivore (female) is neither hungry nor thirsty
              if(m_thirst < (config::MAX_THIRST*3/4) && m_hunger < (config::MAX_HUNGER*3/4))
              {
                  World::mutexMateList.lock();
                  m_world->updateMateList(this, herbivoreToMate);
                  World::mutexMateList.unlock();
                  return true;
              }
          }
       }
    }
    return false;
}
