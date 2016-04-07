#include "World.h"
#include "Animal.h"

#include <iostream>
using namespace std;

World::World()
{
    //don't work: aply a modulus by WORLD_SIZE so always 0...
    //m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
    m_size_x = WORLD_SIZE_X;
    m_size_y = WORLD_SIZE_Y;
}

std::vector<shared_ptr<Entity>> &World::getEntities()
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

int World::tick()
{
    int entityErrorsNum = 0;
    int i=0;
    for(shared_ptr<Entity> e:m_entities)
    {
        if(e->play())
        {
            //TODO : manage entities errors
            std::cerr << "Entity no " << i << " failed to play" << std::endl;
            entityErrorsNum++;
        }
        i++;
      //  if(Animal* animal = dynamic_cast<Animal*>(m_entities.at(i)))
      //  {
           /*if(animal->isDead())
           {
             delete m_entities.at(i);
             m_entities.at(i) = nullptr;
             m_entities.erase(m_entities.begin()+i);
          }*/
      //  }

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
  int i = 0;
  for(shared_ptr<Entity> currentEntity : m_entities)
  {
      if(e == currentEntity)
        break;
      i++;
  }
  m_entities.erase(m_entities.begin() + i); // RIP
}

// private methods

bool World::isCollision(const shared_ptr<Entity> e1, const shared_ptr<Entity> e2) const
{
    const Coordinate & c1 = e1->getCoordinate();
    const Coordinate & c2 = e2->getCoordinate();
    return (Coordinate::getDistance(c1,c2) < (e1->getRadius() + e2->getRadius()));
}







