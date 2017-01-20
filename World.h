#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <thread>
#include <mutex>

#include "NeuralNetwork.h"
#include "Resource.h"

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

    unsigned int getGenerationNumber() const { return m_generationNumber; };

    //I'm as wise as the world. Oh wait...
    unsigned getWorldAge() const {return m_tickPassed;}

    void setWorldAge(unsigned tickPassed) {m_tickPassed = tickPassed;}
    void setSize(int size_x, int size_y);
    void setGenerationNumber(unsigned generationNumber) {m_generationNumber = generationNumber;}

    void updateListCollision(std::shared_ptr<Animal> a) const;
    void updateAttackList(std::shared_ptr<Animal> a, double damage);

    void updateMateList(Animal * female, std::shared_ptr<Animal> male);

    void updateGridOfEntities(std::shared_ptr<Animal> a, int oldX, int oldY, int newX, int newY);

    //More ! Give me more of them !
    void addAnimal(std::shared_ptr<Animal> animal);
    static void addResource(std::shared_ptr<Resource> resource);
    void feedWithRandomAnimal(unsigned short numberOfEntityToAdd);
    void feedWithRandomHerbivore(unsigned short numberOfEntityToAdd);
    void feedWithRandomCarnivore(unsigned short numberOfEntityToAdd);
    void feedWithChildOfChampionHerbivore(unsigned short numberOfEntityToAdd);
    void feedWithChildOfChampionCarnivore(unsigned short numberOfEntityToAdd);

    //I'm also almost the master of the time, I can make the world tic for you !
    int tick();
    int tick(int ticsNum);

    // Mutex - protect access while multithreading
    static std::mutex mutexGetEntity;
    static std::mutex mutexAttributes;
    static std::mutex mutexGridOfEntities;
    static std::mutex mutexListEntities; // If listEntities and gridEntities must be block together, listEntites should be block before.
    static std::mutex mutexCollisionList;
    static std::mutex mutexDeadList;
    static std::mutex mutexAttackList;
    static std::mutex mutexMateList;
    static std::mutex mutexDrink;
    static std::mutex mutexVegetal;
    static std::mutex mutexMeat;
    static std::mutex mutexChampionSaving;

private:
    //Privates methods
    bool isCollision(const std::shared_ptr<Entity> e1, const std::shared_ptr<Entity> e2) const;
    static void saveNeuralNetworkIfNeeded(std::shared_ptr<Animal> a);
    double computeScore(std::shared_ptr<Animal> animal);
    NeuralNetwork * determineBestNN();
    void createGridOfEntities();
    void makeMoves();
    void makeAttacks();
    void makeMatings();
    void synchronizedListAndGridOfEntities();
    static void removeEntity(std::list<std::shared_ptr<Entity>>::iterator it);

    static void startThreads(std::list<std::shared_ptr<Entity>>::iterator * it, int nbEntities, std::list<std::list<std::shared_ptr<Entity>>::iterator> * deadList);
    static int playAnimals(std::list<std::shared_ptr<Entity>>::iterator * it, int * entitiesCount, int nbEntities, std::list<std::list<std::shared_ptr<Entity>>::iterator> * deadList);

    //Private attributes
    static unsigned m_tickPassed; //How old that world is ?
    static unsigned m_numberOfLiving;
    static unsigned m_numberOfHerbivore;
    static unsigned m_numberOfCarnivore;
    unsigned int m_generationNumber;
    static std::multimap<int,NeuralNetwork> bestHerbivore;
    static std::multimap<int,NeuralNetwork> bestCarnivore;
    std::list<std::pair<std::shared_ptr<Animal>,double>> m_attackList;
    std::list<std::pair<Herbivore*,std::shared_ptr<Herbivore>>> m_mateListHerbivores;
    std::list<std::pair<Carnivore*,std::shared_ptr<Carnivore>>> m_mateListCarnivores;

    //My loves, my life
    static unsigned int m_cellSizeX;
    static unsigned int m_cellSizeY;
    static std::list<std::shared_ptr<Entity>> m_entities; // Resources are from 0 to nbResources, and animals from nbResources + 1 to list.size() - 1
    static std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> m_gridOfEntities;

    int m_size_x;
    int m_size_y;
};

#endif // WORLD_H
