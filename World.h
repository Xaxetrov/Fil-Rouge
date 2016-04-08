#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <list>
#include "Entity.h"
#include "Animal.h"

class Animal;
/*
 * The world is... the world
 */
class World
{
public:
    //Public methods

    // THE CONSTRUCTOR OF THE WORLD ! MOUHAHAHAHAHAAAAAAAAAAAAAAAAA !
    World();

    //Do you wanna get my entities ?
    std::list<std::shared_ptr<Entity> > &getEntities();

    //Why do you want it ? I'm the biggest world of all worlds !
    //Coordinate & getSize(); disabled as not working :/
    //What did I just told you ? It's useless !
    int getSizeX() const;
    //You sir are hopeless...
    int getSizeY() const;

    void setSize(int size_x, int size_y);

    void updateListCollision(std::shared_ptr<Animal> a) const;

    //More ! Give me more of them !
    void addEntity(std::shared_ptr<Entity> entity);

    //I'm also almost the master of the time, I can make the world tic for you !
    int tick();
    int tick(int ticsNum);

    void killEntity(std::shared_ptr<Entity> e); // MOUHAHAHAHAHAAAAAAAAAAAAAAAAA

private:
    //Privates methods
    bool isCollision(const std::shared_ptr<Entity> e1, const std::shared_ptr<Entity> e2) const;

    //Private attributes

    //My loves, my life
    std::list<std::shared_ptr<Entity>> m_entities;
    int m_size_x;
    int m_size_y;
};

#endif // WORLD_H
