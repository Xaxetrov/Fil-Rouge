#include "World.h"
#include "Animal.h"

#include <algorithm>
#include <iostream>
using namespace std;

World::World()
{
    //don't work: aply a modulus by WORLD_SIZE so always 0...
    //m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
    m_size_x = WORLD_SIZE_X;
    m_size_y = WORLD_SIZE_Y;
    m_numberOfLiving = 0;
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

void World::feadWidthRandomAnimal(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % WORLD_SIZE_X;
      int y = rand() % WORLD_SIZE_Y;
      shared_ptr<Animal> animal(make_shared<Animal>(x, y, 10, 50, 2, this));
      animal->turn( (double)(rand()%628)/100);
      addEntity(animal);
    }
}

int World::tick()
{
    int entityErrorsNum = 0;
    int i=0;
    m_numberOfLiving = 0;
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
            m_numberOfLiving++;
            if(animal->isDead())
            {
                //work arround the fat that the currant cell will be deleted
                std::list<std::shared_ptr<Entity>>::iterator sav = e;
                sav--;
                m_entities.erase(e);
                e=sav;
            }
        }
    }
    if(m_numberOfLiving < MIN_NUMBER_OF_ANIMAL)
    {
        feadWidthRandomAnimal(MIN_NUMBER_OF_ANIMAL-m_numberOfLiving);
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

unsigned World::getNumberOfLiving() const
{
    return m_numberOfLiving;
}
