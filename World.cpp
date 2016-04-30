#include "World.h"
#include "Entity.h"
#include "Animal.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Meat.h"
#include "config/config.h"

#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

World::World()
{
    //don't work: aply a modulus by WORLD_SIZE so always 0...
    //m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
    m_size_x = WORLD_SIZE_X;
    m_size_y = WORLD_SIZE_Y;
    m_tickPassed = 0;
}

std::list<shared_ptr<Entity>> &World::getEntities()
{
    return m_entities;
}

/*Coordinate & World::getSize()
{
    return m_size;
}*/

int World::getSizeX() const
{
    return m_size_x;
}

int World::getSizeY() const
{
    return m_size_y;
}

void World::setSize(int size_x, int size_y)
{
   m_size_x = size_x;
   m_size_y = size_y;
}

void World::updateListCollision(shared_ptr<Animal> a) const
{
    a->clearEntityListCollision();
    for(shared_ptr<Entity> currentEntity : m_entities)
    {
        if(a!=currentEntity && isCollision(a, currentEntity))
        {
            a->addEntityInListCollision(currentEntity);
        }
    }
}

void World::addEntity(shared_ptr<Entity> entity)
{
    m_entities.push_back(entity);
}

void World::feedWithRandomAnimal(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      shared_ptr<Animal> animal(make_shared<Animal>(x, y, INITIAL_RADIUS, MAX_SPEED, ATTACK_ANIMAL, DEFAULT_ENERGY, this));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithRandomHerbivore(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      shared_ptr<Herbivore> animal(make_shared<Herbivore>(x, y, INITIAL_RADIUS, MAX_SPEED, ATTACK_HERBIVORE, DEFAULT_ENERGY, this));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithChildOfChampionHerbivore(unsigned short numberOfEntityToAdd)
{
    if(bestHerbivore.size() == 0)
    {
        return;
    }
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      //generate a brain from the one of the last best herbivore
      //pick one brain randomly
      auto ite = bestHerbivore.begin();
      std::advance(ite,rand() % bestHerbivore.size());
      NeuralNetwork n1 = ite->second;
      //pick an other one randomly (they can be the same...)
      ite = bestHerbivore.begin();
      std::advance(ite,rand() % bestHerbivore.size());
      NeuralNetwork n2 = ite->second;
      //mixe them up
      NeuralNetwork *nn = new NeuralNetwork(n1,n2);
      //make a new Herbivore from that brain
      shared_ptr<Herbivore> animal(make_shared<Herbivore>(x, y, INITIAL_RADIUS, MAX_SPEED, ATTACK_HERBIVORE, DEFAULT_ENERGY, this,nn,MAX_MATING));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithRandomCarnivore(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      shared_ptr<Carnivore> animal(make_shared<Carnivore>(x, y, INITIAL_RADIUS, MAX_SPEED, ATTACK_CARNIVORE, DEFAULT_ENERGY, this));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithChildOfChampionCarnivore(unsigned short numberOfEntityToAdd)
{
    if(bestCarnivore.size() == 0)
    {
        return;
    }
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      //generate a brain from the one of the last best carnivore
      //pick one brain randomly
      auto ite = bestCarnivore.begin();
      std::advance(ite,rand() % bestCarnivore.size());
      NeuralNetwork n1 = ite->second;
      //pick an other one randomly (they can be the same...)
      ite = bestCarnivore.begin();
      std::advance(ite,rand() % bestCarnivore.size());
      NeuralNetwork n2 = ite->second;
      //mixe them up
      NeuralNetwork *nn = new NeuralNetwork(n1,n2);
      //make a new Carnivore from that brain
      shared_ptr<Carnivore> animal(make_shared<Carnivore>(x, y, INITIAL_RADIUS, MAX_SPEED, ATTACK_CARNIVORE, DEFAULT_ENERGY, this,nn,MAX_MATING));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

int World::tick()
{
    int entityErrorsNum = 0;
    int i=0;
    m_numberOfLiving = 0;
    m_numberOfCarnivore = 0;
    m_numberOfHerbivore = 0;
    //for(unsigned j = 0; j < m_entities.size(); j++)
    //for(shared_ptr<Entity> e:m_entities)
    for(std::list<std::shared_ptr<Entity>>::iterator e=m_entities.begin() ; e!=m_entities.end() ; ++e)
    {
        //shared_ptr<Entity> e = m_entities[j];
        if((*e)->play())
        {
            //TODO : manage entities errors
            std::cerr << "Entity no " << i << " failed to play" << std::endl;
            entityErrorsNum++;
        }
        i++;
        if(shared_ptr<Animal> animal = dynamic_pointer_cast<Animal>(*e))
        {
            if(animal->isDead())
            {
#ifdef FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
                saveNeuralNetwork(animal);
#endif
                int meatQuantity = MAX_HUNGER - animal->getHunger();
                m_entities.push_back(make_shared<Meat>(animal->getCoordinate(),animal->getRadius(),meatQuantity));
            }
            else
            {
                m_numberOfLiving++;
                switch (animal->getTypeId()) {
                case ID_CARNIVORE:
                    m_numberOfCarnivore++;
                    break;
                case ID_HERBIVORE:
                    m_numberOfHerbivore++;
                    break;
                default:
                    break;
                }
            }
        }
        if((*e)->isDead())
        {
            //work arround the fat that the currant cell will be deleted
            std::list<std::shared_ptr<Entity>>::iterator sav = e;
            sav--;
            m_entities.erase(e);
            e=sav;
        }
    }
    //incremente the age of the world
    m_tickPassed++;
    /*if(m_numberOfLiving < MIN_NUMBER_OF_ANIMAL)
    {
        feedWithRandomHerbivore(MIN_NUMBER_OF_ANIMAL-m_numberOfLiving);
    }*/
    if(m_numberOfCarnivore < MIN_NUMBER_OF_CARNIVORE)
    {
        #ifdef FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
            feedWithChildOfChampionCarnivore(MIN_NUMBER_OF_CARNIVORE-m_numberOfCarnivore);
        #else
            feedWithRandomCarnivore(MIN_NUMBER_OF_CARNIVORE-m_numberOfCarnivore);
        #endif
    }
    if(m_numberOfHerbivore < MIN_NUMBER_OF_HERBVORE)
    {
        #ifdef FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
            feedWithChildOfChampionHerbivore(MIN_NUMBER_OF_HERBVORE-m_numberOfHerbivore);
        #else
            feedWithRandomHerbivore(MIN_NUMBER_OF_HERBVORE-m_numberOfHerbivore);
        #endif
    }
    return entityErrorsNum;
}

int World::tick(int ticNum)
{
    for(int i=0; i<ticNum; i++)
    {
        if(tick())
        {
            //TODO : manage tic errors
        }
    }
    return 0;
}

void World::killEntity(shared_ptr<Entity> e)
{
    m_entities.erase(find(m_entities.begin(),m_entities.end(),e)); //RIP
}

// private methods

bool World::isCollision(const shared_ptr<Entity> e1, const shared_ptr<Entity> e2) const
{
    const Coordinate & c1 = e1->getCoordinate();
    const Coordinate & c2 = e2->getCoordinate();
    return (Coordinate::getDistance(c1,c2) < (e1->getRadius() + e2->getRadius()));
}

void World::saveNeuralNetwork(std::shared_ptr<Animal> a)
{
    int age = getWorldAge() - a->getCreationDate();
    if(shared_ptr<Herbivore> h = dynamic_pointer_cast<Herbivore>(a))
    {
        if(bestHerbivore.size()==0 || bestHerbivore.rbegin()->first < age )
        {
            bestHerbivore.insert(std::pair<int,NeuralNetwork>(age,*(h->getBrain())) );
        }
        if(bestHerbivore.size() > MAX_NUMBER_HERBIVORE_CHAMPION)
        {
            bestHerbivore.erase(bestHerbivore.begin());
        }
    }
    else if(shared_ptr<Carnivore> c = dynamic_pointer_cast<Carnivore>(a))
    {
        if(bestCarnivore.size()==0 || bestCarnivore.rbegin()->first < age )
        {
            bestCarnivore.insert(std::pair<int,NeuralNetwork>(age,*(c->getBrain())) );
        }
        if(bestCarnivore.size() > MAX_NUMBER_HERBIVORE_CHAMPION)
        {
            bestCarnivore.erase(bestCarnivore.begin());
        }
    }
}

unsigned World::getNumberOfLiving() const
{
    return m_numberOfLiving;
}
