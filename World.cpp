#include "World.h"
#include "Animal.h"

#include <iostream>

World::World()
{
    //don't work: aply a modulus by WORLD_SIZE so always 0...
    //m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
    m_size_x = WORLD_SIZE_X;
    m_size_y = WORLD_SIZE_Y;
}

std::vector<Entity *> &World::getEntities()
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

bool World::isCollision(const Entity* e) const
{
    for(Entity* currentEntity : m_entities)
    {
        if(e!=currentEntity && isCollision(e, currentEntity))
        {
            return true;
        }
    }
    return false;
}

void World::addEntity(Entity *entity)
{
    m_entities.push_back(entity);
}

int World::tick()
{
    int entityErrorsNum = 0;
    for(unsigned int i=0; i<m_entities.size(); i++)
    {
        if(m_entities.at(i)->play())
        {
            //TODO : manage entities errors
            std::cerr << "Entity no " << i << " failed to play" << std::endl;
            entityErrorsNum++;
        }
        if(Animal* animal = dynamic_cast<Animal*>(m_entities.at(i)))
        {
           /*if(animal->isDead())
           {
             delete m_entities.at(i);
             m_entities.at(i) = nullptr;
             m_entities.erase(m_entities.begin()+i);
          }*/
        }

    }
    return entityErrorsNum;
}

int World::tick(int ticNum)
{
    int tickResult=0;
    for(int i=0; i<ticNum; i++)
    {
        if(tick())
        {
            //TODO : manage tic errors
        }
    }
}

// private methods

bool World::isCollision(const Entity *e1, const Entity *e2) const
{
    const Coordinate * c1 = e1->getCoordinate();
    const Coordinate * c2 = e2->getCoordinate();
    return(Coordinate::getDistance(*c1, *c2) < (e1->getRadius()+e2->getRadius()) );
}
