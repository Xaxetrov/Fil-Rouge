#include "Carnivore.h"
#include "Meat.h"


Carnivore::Carnivore(double x, double y, int radius, int maxSpeed, double damage, World *world):
    Animal(x,y,radius,maxSpeed,damage,world)
{
    m_attack = ATTACK_CARNIVORE;
}
Carnivore::Carnivore(double x, double y, int radius, int maxSpeed, double damage, World *world, bool sex):
    Animal(x,y,radius,maxSpeed,damage,world, sex)
{
    m_attack = ATTACK_CARNIVORE;
}

Carnivore::Carnivore(double x, double y, int radius, int maxSpeed, double damage, World *world, NeuralNetwork * brain, int mating):
    Animal(x,y,radius,maxSpeed,damage,world, brain, mating)
{
    m_attack = ATTACK_CARNIVORE;
}


void Carnivore::tryToEat(std::shared_ptr<Entity> food)
{
    //Carenivore are... carnivore... so they try to eat meat !
    if(shared_ptr<Meat> meat = dynamic_pointer_cast<Meat>(food))
    {
       if(m_hunger > 0)
       {
           int quantity = std::min(EAT_MAX_MEAT_QUANTITY,(unsigned)m_hunger);
           m_hunger -= meat->eat(quantity);
       }
       //heal himself
       if(m_health < MAX_HEALTH && m_thirst < MAX_THIRST*3/4)
       {
           m_health += std::min(EAT_MAX_HEALING_VALUE,(unsigned)(MAX_HEALTH-m_health));
       }
    }
}

bool Carnivore::tryToMate(std::shared_ptr<Entity> carnivoreEntity)
{
    if(shared_ptr<Carnivore> carnivoreToMate = dynamic_pointer_cast<Carnivore>(carnivoreEntity))
    {
       // this Animal is the female
       if(m_female && !carnivoreToMate->isFemale())
       {
           //both carnivore are ready to mate
          if(m_mating == MAX_MATING && carnivoreToMate->getMating() == MAX_MATING)
          {
              //this carnivore (female) is neither hungry nor thirsty
              if(m_thirst < (MAX_THIRST*3/4) && m_hunger < (MAX_HUNGER*3/4))
              {
                  reproduce(carnivoreToMate);
                  return true;
              }
          }
       }
    }
    return false;
}


