#include "Carnivore.h"
#include "Meat.h"


Carnivore::Carnivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int generationNumber, World *world):
    Animal(x,y,maxSpeed,damage,energy,generationNumber,world)
{
}
Carnivore::Carnivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int generationNumber, World *world, bool sex):
    Animal(x,y,maxSpeed,damage,energy,generationNumber,world, sex)
{
}

Carnivore::Carnivore(double x, double y, int maxSpeed, double damage, double energy, unsigned int generationNumber, World *world, NeuralNetwork * brain, int mating):
    Animal(x,y,maxSpeed,damage,energy,generationNumber,world, brain, mating)
{
}


void Carnivore::tryToEat(std::shared_ptr<Entity> food)
{
    //Carenivore are... carnivore... so they try to eat meat !
    if(std::shared_ptr<Meat> meat = std::dynamic_pointer_cast<Meat>(food))
    {
       if(m_hunger > 0)
       {
           int quantity = std::min(config::EAT_MAX_MEAT_QUANTITY,(unsigned)m_hunger);
           World::mutexMeat.lock();
           double eatenQuantity = meat->eat(quantity);
           World::mutexMeat.unlock();
           m_hunger -= eatenQuantity;
           //m_radius += config::FATNESS_CARNIVORE * eatenQuantity;
       }
       //heal himself
       if(m_health < config::MAX_HEALTH && m_thirst < config::MAX_THIRST*3/4)
       {
           m_health += std::min(config::EAT_MAX_HEALING_VALUE,(unsigned)(config::MAX_HEALTH-m_health));
       }
    }
}

bool Carnivore::tryToMate(std::shared_ptr<Entity> carnivoreEntity)
{
    if(std::shared_ptr<Carnivore> carnivoreToMate = std::dynamic_pointer_cast<Carnivore>(carnivoreEntity))
    {
       // this Animal is the female
       if(m_female && !carnivoreToMate->isFemale())
       {
           //both carnivore are ready to mate
          if(m_mating == config::MAX_MATING && carnivoreToMate->getMating() == config::MAX_MATING)
          {
              //this carnivore (female) is neither hungry nor thirsty
              if(m_thirst < (config::MAX_THIRST*3/4) && m_hunger < (config::MAX_HUNGER*3/4))
              {
                  World::mutexMateList.lock();
                  m_world->updateMateList(this->shared_from_this(), carnivoreToMate);
                  World::mutexMateList.unlock();
                  return true;
              }
          }
       }
    }
    return false;
}
