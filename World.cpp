#include "World.h"
#include "Entity.h"
#include "Animal.h"
#include "Herbivore.h"
#include "Carnivore.h"
#include "Meat.h"
#include "config/config.h"
#include "Timelinewidget.h"

#include <algorithm>
#include <iostream>
#include <map>

World::World()
{
    //don't work: aply a modulus by WORLD_SIZE so always 0...
    //m_size.set(WORLD_SIZE_X,WORLD_SIZE_Y);
    m_size_x = config::WORLD_SIZE_X;
    m_size_y = config::WORLD_SIZE_Y;
    m_tickPassed = 0;

    createGridOfEntities();
}

const std::list<std::shared_ptr<Entity>> &World::getEntities() const
{
    return m_entities;
}

std::list<std::shared_ptr<Entity>> World::getCopyOfEntities() const
{
    return m_entities;
}

const std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> & World::getGridOfEntities() const
{
    return m_gridOfEntities;
}

int World::getCellSizeX() const
{
    return m_cellSizeX;
}

int World::getCellSizeY() const
{
    return m_cellSizeY;
}

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
   config::WORLD_SIZE_X = size_x;
   config::WORLD_SIZE_Y = size_y;

   createGridOfEntities();
   synchronizedListAndGridOfEntities();

}

void World::updateListCollision(std::shared_ptr<Animal> a) const
{
    a->clearEntityListCollision();
    for(std::shared_ptr<Entity> currentEntity : m_entities)
    {
        if(a!=currentEntity && isCollision(a, currentEntity))
        {
            a->addEntityInListCollision(currentEntity);
        }
    }
}

void World::updateGridOfEntities(std::shared_ptr<Animal> a, int oldX, int oldY, int newX, int newY)
{
    int oldCellX = oldX / m_cellSizeX;
    int newCellX = newX / m_cellSizeX;
    int oldCellY = oldY / m_cellSizeY;
    int newCellY = newY / m_cellSizeY;

    if (oldCellX != newCellX || oldCellY != newCellY)
    {
        m_gridOfEntities[oldCellX][oldCellY].erase(find(m_gridOfEntities[oldCellX][oldCellY].begin(), m_gridOfEntities[oldCellX][oldCellY].end(), a));
        m_gridOfEntities[newCellX][newCellY].push_back(a);
    }
}

void World::addEntity(std::shared_ptr<Entity> entity)
{
    m_entities.push_back(entity);
    m_gridOfEntities[entity->getX() / m_cellSizeX][entity->getY() / m_cellSizeY].push_back(entity);
}

void World::feedWithRandomAnimal(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % config::WORLD_SIZE_X;
      int y = rand() % config::WORLD_SIZE_Y;
      std::shared_ptr<Animal> animal(std::make_shared<Animal>(x, y, config::INITIAL_RADIUS, config::MAX_SPEED, config::ATTACK_ANIMAL, config::DEFAULT_ENERGY, this));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithRandomHerbivore(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % config::WORLD_SIZE_X;
      int y = rand() % config::WORLD_SIZE_Y;
      std::shared_ptr<Herbivore> animal(std::make_shared<Herbivore>(x, y, config::INITIAL_RADIUS, config::MAX_SPEED, config::ATTACK_HERBIVORE, config::DEFAULT_ENERGY, this));
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
      int x = rand() % config::WORLD_SIZE_X;
      int y = rand() % config::WORLD_SIZE_Y;
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
      std::shared_ptr<Herbivore> animal(std::make_shared<Herbivore>(x, y, config::INITIAL_RADIUS, config::MAX_SPEED, config::ATTACK_HERBIVORE, config::DEFAULT_ENERGY, this,nn,config::MAX_MATING));
      animal->turn( (double)(rand()%628)/100.0);
      addEntity(animal);
    }
}

void World::feedWithRandomCarnivore(unsigned short numberOfEntityToAdd)
{
    for(unsigned short i = 0; i < numberOfEntityToAdd; i++)
    {
      int x = rand() % config::WORLD_SIZE_X;
      int y = rand() % config::WORLD_SIZE_Y;
      std::shared_ptr<Carnivore> animal(std::make_shared<Carnivore>(x, y, config::INITIAL_RADIUS, config::MAX_SPEED, config::ATTACK_CARNIVORE, config::DEFAULT_ENERGY, this));
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
      int x = rand() % config::WORLD_SIZE_X;
      int y = rand() % config::WORLD_SIZE_Y;
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
      std::shared_ptr<Carnivore> animal(std::make_shared<Carnivore>(x, y, config::INITIAL_RADIUS, config::MAX_SPEED, config::ATTACK_CARNIVORE, config::DEFAULT_ENERGY, this,nn,config::MAX_MATING));
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
    for(std::list<std::shared_ptr<Entity>>::iterator e = m_entities.begin(); e != m_entities.end(); ++e)
    {
        //shared_ptr<Entity> e = m_entities[j];
        if((*e)->play())
        {
            //TODO : manage entities errors
            std::cerr << "Entity no " << i << " failed to play" << std::endl;
            entityErrorsNum++;
        }
        i++;
        if(std::shared_ptr<Animal> animal = std::dynamic_pointer_cast<Animal>(*e))
        {
            if(animal->isDead())
            {
#ifdef FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
                saveNeuralNetwork(animal);
#endif
                int meatQuantity = config::MAX_HUNGER - animal->getHunger();
                m_entities.push_back(std::make_shared<Meat>(animal->getCoordinate(),animal->getRadius(),meatQuantity));
                m_gridOfEntities[animal->getX() / m_cellSizeX][animal->getY() / m_cellSizeY].push_back(*(--m_entities.end()));
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
            //work arround the fact that the currant cell will be deleted
            std::list<std::shared_ptr<Entity>>::iterator sav = e;
            m_entities.erase(e);
            m_gridOfEntities[(*sav)->getX() / m_cellSizeX][(*sav)->getY() / m_cellSizeY].erase(find(m_gridOfEntities[(*sav)->getX() / m_cellSizeX]
                    [(*sav)->getY() / m_cellSizeY].begin(), m_gridOfEntities[(*sav)->getX() / m_cellSizeX][(*sav)->getY() / m_cellSizeY].end(),*sav));
            sav--;
            e=sav;
        }
    }
    //incremente the age of the world
    m_tickPassed++;

    TimelineWidget::updatePopulation(m_numberOfHerbivore, m_numberOfCarnivore, m_tickPassed);

    // TO DEBUG
    /*NeuralNetwork *bestNeuralNetwork = determineBestNN();
    if (m_tickPassed % 1000 == 0)
    {   for(std::list<std::shared_ptr<Entity>>::iterator it=m_entities.begin() ; it!=m_entities.end() ; ++it)
        {
            if(std::shared_ptr<Animal> animal = std::dynamic_pointer_cast<Animal>(*it))
            {
                animal->evolve(bestNeuralNetwork);
            }
        }
    }*/

    
    /*if(m_numberOfLiving < MIN_NUMBER_OF_ANIMAL)
    {
        feedWithRandomHerbivore(MIN_NUMBER_OF_ANIMAL-m_numberOfLiving);
    }*/
    if(m_numberOfCarnivore < config::MIN_NUMBER_OF_CARNIVORE)
    {
        #ifdef FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
            feedWithChildOfChampionCarnivore(config::MIN_NUMBER_OF_CARNIVORE-m_numberOfCarnivore);
        #else
            feedWithRandomCarnivore(config::MIN_NUMBER_OF_CARNIVORE-m_numberOfCarnivore);
        #endif
    }
    if(m_numberOfHerbivore < config::MIN_NUMBER_OF_HERBVORE)
    {
        #ifdef config::FEED_WORLD_WITH_CHILD_OF_CHAMPIONS
            feedWithChildOfChampionHerbivore(config::MIN_NUMBER_OF_HERBVORE-m_numberOfHerbivore);
        #else
            feedWithRandomHerbivore(config::MIN_NUMBER_OF_HERBVORE-m_numberOfHerbivore);
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

void World::killEntity(std::shared_ptr<Entity> e)
{
    m_entities.erase(find(m_entities.begin(),m_entities.end(),e)); //RIP
    m_gridOfEntities[e->getX() / m_cellSizeX][e->getY() / m_cellSizeY].erase(find(m_gridOfEntities[e->getX() / m_cellSizeX]
            [e->getY() / m_cellSizeY].begin(), m_gridOfEntities[e->getX() / m_cellSizeX][e->getY() / m_cellSizeY].end(), e));
}

// private methods

bool World::isCollision(const std::shared_ptr<Entity> e1, const std::shared_ptr<Entity> e2) const
{
    const Coordinate & c1 = e1->getCoordinate();
    const Coordinate & c2 = e2->getCoordinate();
    double r1 = e1->getRadius();
    double r2 = e2->getRadius();
    return (Coordinate::getDistanceCarre(c1,c2) < (r1 + r2) * (r1 + r2));
}

void World::saveNeuralNetwork(std::shared_ptr<Animal> a)
{
    int age = getWorldAge() - a->getCreationDate();
    if(std::shared_ptr<Herbivore> h = std::dynamic_pointer_cast<Herbivore>(a))
    {
        if(bestHerbivore.size()==0 || bestHerbivore.rbegin()->first < age )
        {
            bestHerbivore.insert(std::pair<int,NeuralNetwork>(age,*(h->getBrain())) );
        }
        if(bestHerbivore.size() > config::MAX_NUMBER_HERBIVORE_CHAMPION)
        {
            bestHerbivore.erase(bestHerbivore.begin());
        }
    }
    else if(std::shared_ptr<Carnivore> c = std::dynamic_pointer_cast<Carnivore>(a))
    {
        if(bestCarnivore.size()==0 || bestCarnivore.rbegin()->first < age )
        {
            bestCarnivore.insert(std::pair<int,NeuralNetwork>(age,*(c->getBrain())) );
        }
        if(bestCarnivore.size() > config::MAX_NUMBER_HERBIVORE_CHAMPION)
        {
            bestCarnivore.erase(bestCarnivore.begin());
        }
    }
}

double World::computeScore(std::shared_ptr<Animal> animal)
/* 100% health = 100% health score, 50% health = 75% health score and 0% health = 0% health score
 * 0% hunger = 100% hunger score, 50% hunger = 75% hunger score, 100% hunger = 0% hunger score
 * same things for thirst and fear
 * Illustrate the fact that to get a little hungry does not have the same gravity as to starve !
 */
{
    double a = 1.125*config::MAX_SCORE;
    double b = (0.5*config::MAX_HEALTH) / (log(a-0.75*config::MAX_SCORE)-log(a-config::MAX_SCORE));
    double c = log(a);
    double healthScore = a - exp(-animal->getHealth()/b+c);

    b = (0.5*config::MAX_HUNGER) / (log(a) - log(a-0.75*config::MAX_SCORE));
    c = log(a-config::MAX_SCORE);
    double hungerScore = a - exp(animal->getHunger()/b+c);

    b = (0.5*config::MAX_THIRST) / (log(a) - log(a-0.75*config::MAX_SCORE));
    double thirstScore = a - exp(animal->getThirst()/b+c);

    b = (0.5*config::MAX_FEAR) / (log(a) - log(a-0.75*config::MAX_SCORE));
    double fearScore = a - exp(animal->getFear()/b+c);

    return (2*healthScore+hungerScore+thirstScore+2*fearScore)/6; // Balance the various criteria
}

NeuralNetwork * World::determineBestNN ()
/* allows to determine the animal of which the neural network has been the most effective recently :
 * it score has increased most during last tics
 * OR
 * it score is max
 */
{   double diffScore = 0;
    double diffScoreMax = 0;
    NeuralNetwork *bestNN = nullptr;
    for(std::list<std::shared_ptr<Entity>>::iterator it=m_entities.begin() ; it!=m_entities.end() ; ++it)
    {
        if(std::shared_ptr<Animal> animal = std::dynamic_pointer_cast<Animal>(*it))
        {
            diffScore = -1 * animal->getScore();
            animal->setScore(this->computeScore(animal));
            diffScore += animal->getScore();
            if (diffScore > diffScoreMax || animal->getScore() == config::MAX_SCORE)
            {   bestNN = animal->evolveNN();
            }
        }
    }
    return bestNN;
}

void World::createGridOfEntities()
{
    for (m_cellSizeX = MAX_RANGE_OF_VISION; m_size_x % m_cellSizeX; m_cellSizeX++); // m_cellSizeX prend le plus petit diviseur de m_size_x supérieur a MAX_RANGE_OF_VISION
    for (m_cellSizeY = MAX_RANGE_OF_VISION; m_size_y % m_cellSizeY; m_cellSizeY++); // Idem

    m_gridOfEntities.clear();
    // Create an empty grid of the right size.
    std::vector<std::list<std::shared_ptr<Entity>>> standartElementDimension1;
    std::list<std::shared_ptr<Entity>> standartElementDimension2;
    for (unsigned int i = 0; i < m_size_x / m_cellSizeX; i++)
    {
        m_gridOfEntities.push_back(standartElementDimension1);
        for (unsigned int j = 0; j < m_size_y / m_cellSizeY; j++)
        {
            m_gridOfEntities[i].push_back(standartElementDimension2);
        }
    }
}

void World::synchronizedListAndGridOfEntities()
{
    for (std::shared_ptr<Entity> entity : m_entities)
    {
        m_gridOfEntities[entity->getX() / m_cellSizeX][entity->getY() / m_cellSizeY].push_back(entity);
    }
}

unsigned World::getNumberOfLiving() const
{
    return m_numberOfLiving;
}
