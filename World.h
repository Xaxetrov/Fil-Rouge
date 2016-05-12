#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <list>
#include <map>

#include "NeuralNetwork.h"

class Entity;
class Animal;
class Herbivore;
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
    const std::list<std::shared_ptr<Entity> > &getEntities() const;
    std::list<std::shared_ptr<Entity> >  getCopyOfEntities() const;
    const std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> & getGridOfEntities() const;

    unsigned getNumberOfLiving() const;

    //Why do you want it ? I'm the biggest world of all worlds !
    //Coordinate & getSize(); disabled as not working :/
    //What did I just told you ? It's useless !
    int getSizeX() const;
    //You sir are hopeless...
    int getSizeY() const;
    int getCellSizeX() const;
    int getCellSizeY() const;

    //I'm as wise as the world. Oh wait...
    unsigned getWorldAge() const {return m_tickPassed;}

    void setWorldAge(unsigned tickPassed) {m_tickPassed = tickPassed;}
    void setSize(int size_x, int size_y);

    void updateListCollision(std::shared_ptr<Animal> a) const;
    void updateGridOfEntities(std::shared_ptr<Animal> a, int oldX, int oldY, int newX, int newY);

    //More ! Give me more of them !
    void addEntity(std::shared_ptr<Entity> entity);
    void feedWithRandomAnimal(unsigned short numberOfEntityToAdd);
    void feedWithRandomHerbivore(unsigned short numberOfEntityToAdd);
    void feedWithRandomCarnivore(unsigned short numberOfEntityToAdd);
    void feedWithChildOfChampionHerbivore(unsigned short numberOfEntityToAdd);
    void feedWithChildOfChampionCarnivore(unsigned short numberOfEntityToAdd);

    //I'm also almost the master of the time, I can make the world tic for you !
    int tick();
    int tick(int ticsNum);

    void killEntity(std::shared_ptr<Entity> e); // MOUHAHAHAHAHAAAAAAAAAAAAAAAAA

private:
    //Privates methods
    bool isCollision(const std::shared_ptr<Entity> e1, const std::shared_ptr<Entity> e2) const;
    void saveNeuralNetwork(std::shared_ptr<Animal> a);
    double computeScore(std::shared_ptr<Animal> animal);
    NeuralNetwork * determineBestNN();
    void createGridOfEntities();
    void synchronizedListAndGridOfEntities();

    //Private attributes
    unsigned m_tickPassed; //How old that world is ?
    unsigned m_numberOfLiving;
    unsigned m_numberOfHerbivore;
    unsigned m_numberOfCarnivore;
    std::multimap<int,NeuralNetwork> bestHerbivore;
    std::multimap<int,NeuralNetwork> bestCarnivore;

    //My loves, my life
    unsigned int m_cellSizeX;
    unsigned int m_cellSizeY;
    std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> m_gridOfEntities;
    std::list<std::shared_ptr<Entity>> m_entities;
    int m_size_x;
    int m_size_y;
};

#endif // WORLD_H
