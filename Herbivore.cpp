#include "Herbivore.h"
#include "Vegetal.h"


Herbivore::Herbivore(double x, double y, int radius, int maxSpeed, double damage, World *world):
    Animal(x,y,radius,maxSpeed,damage,world)
{
    m_attack = ATTACK_HERBIVORE;
}
Herbivore::Herbivore(double x, double y, int radius, int maxSpeed, double damage, World *world, bool sex):
    Animal(x,y,radius,maxSpeed,damage,world, sex)
{
    m_attack = ATTACK_HERBIVORE;
}

Herbivore::Herbivore(double x, double y, int radius, int maxSpeed, double damage, World *world, NeuralNetwork * brain, int mating):
    Animal(x,y,radius,maxSpeed,damage,world, brain, mating)
{
    m_attack = ATTACK_HERBIVORE;
}


void Herbivore::tryToEat(std::shared_ptr<Entity> food)
{
    //Herbivore are... herbivore... so they try to eat vegetal
    if(shared_ptr<Vegetal> vegetal = dynamic_pointer_cast<Vegetal>(food))
    {
       if(m_hunger > 0)
       {
           int quantity = std::min(EAT_MAX_VEGETAL_QUANTITY,(unsigned)m_hunger);
           m_hunger -= vegetal->eat(quantity);
       }
       //heal himself
       if(m_health < MAX_HEALTH && m_thirst < MAX_THIRST*3/4)
       {
           m_health += std::min(EAT_MAX_HEALING_VALUE,(unsigned)(MAX_HEALTH-m_health));
       }
    }
}

bool Herbivore::tryToMate(std::shared_ptr<Entity> herbivoreEntity)
{
    if(shared_ptr<Herbivore> herbivoreToMate = dynamic_pointer_cast<Herbivore>(herbivoreEntity))
    {
       // this Animal is the female
       if(m_female && !herbivoreToMate->isFemale())
       {
            //both herbivore are ready to mate
          if(m_mating == MAX_MATING && herbivoreToMate->getMating() == MAX_MATING)
          {
              //this herbivore (female) is neither hungry nor thirsty
              if(m_thirst < (MAX_THIRST*3/4) && m_hunger < (MAX_HUNGER*3/4))
              {
                 reproduce(herbivoreToMate);
                 return true;
              }
          }
       }
    }
    return false;
}