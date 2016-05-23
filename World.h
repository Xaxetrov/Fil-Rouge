#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <mutex>

#include "NeuralNetwork.h"

class Entity;
class Animal;
class Herbivore;
class Carnivore;
/*
 * The world is... the world
 */
class World : public std::enable_shared_from_this<Animal>
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
    void updateAttackList(std::shared_ptr<Animal> a, double damage);

    void updateMateList(Animal * female, std::shared_ptr<Animal> male);

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

    // Mutex - protect access while multithreading
    static std::mutex mutexGetEntity;
    static std::mutex mutexAttributes;
    static std::mutex mutexGridOfEntities;
    static std::mutex mutexListEntities;
    static std::mutex mutexCollisionList;
    static std::mutex mutexDeadList;
    static std::mutex mutexAttackList;
    static std::mutex mutexMateList;
    static std::mutex mutexDrink;
    static std::mutex mutexVegetal;
    static std::mutex mutexMeat;

private:
    //Privates methods
    bool isCollision(const std::shared_ptr<Entity> e1, const std::shared_ptr<Entity> e2) const;
    void saveNeuralNetwork(std::shared_ptr<Animal> a);
    double computeScore(std::shared_ptr<Animal> animal);
    NeuralNetwork * determineBestNN();
    void createGridOfEntities();
    void makeMoves();
    void makeAttacks();
    void makeMatings();
    void synchronizedListAndGridOfEntities();

    static void startThreads(std::list<std::shared_ptr<Entity>>::iterator * it, int * entitiesCount, int nbEntities, std::list<std::list<std::shared_ptr<Entity>>::iterator> * deadList);
    static int playAnimals(std::list<std::shared_ptr<Entity>>::iterator * it, int * entitiesCount, int nbEntities, std::list<std::list<std::shared_ptr<Entity>>::iterator> * deadList);

    //Private attributes
    unsigned m_tickPassed; //How old that world is ?
    static unsigned m_numberOfLiving;
    static unsigned m_numberOfHerbivore;
    static unsigned m_numberOfCarnivore;
    std::multimap<int,NeuralNetwork> bestHerbivore;
    std::multimap<int,NeuralNetwork> bestCarnivore;
    std::list<std::pair<std::shared_ptr<Animal>,double>> m_attackList;
    std::list<std::pair<Herbivore*,std::shared_ptr<Herbivore>>> m_mateListHerbivores;
    std::list<std::pair<Carnivore*,std::shared_ptr<Carnivore>>> m_mateListCarnivores;

    //My loves, my life
    static unsigned int m_cellSizeX;
    static unsigned int m_cellSizeY;
    static std::list<std::shared_ptr<Entity>> m_entities;
    static std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> m_gridOfEntities;

    int m_size_x;
    int m_size_y;
};

#endif // WORLD_H
