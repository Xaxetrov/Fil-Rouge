#ifndef ANIMAL_H
#define ANIMAL_H

#include <memory>
#include <list>
#include <random>

#include "Solid.h"
#include "World.h"
#include "NeuralNetwork.h"
#include "Vision.h"

class Vision;

class Animal : public Solid, public std::enable_shared_from_this<Animal>
{
public:
    //ctor, dtor
    Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world);
    Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, bool sex);
    Animal(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, NeuralNetwork * brain, int mating = 0);
    ~Animal();

    //getters
    int getAge() const;
    int getMaxSpeed() const;
    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getFear() const;
    int getMating() const;
    int getEnergy() const;
    virtual double getScore() const;
    double getSpeed() const;
    double getRotation() const;
    double getDamage() const;
    double getAngle() const;
    const Vision * getVision() const;
    const NeuralNetwork * getBrain() const;
    NeuralNetwork *evolveNN();
    bool isDead() const;
    bool isFemale() const;
    virtual unsigned int getTypeId() const { return ID_ANIMAL; }
    virtual int getNeralNetworkId() const { return NN_ID_ANIMAL; }
    std::vector<std::weak_ptr<Entity> > getSubListCollision(unsigned int idEntity);
    std::vector<std::weak_ptr<Entity> > getSubListSolidCollision();
    std::vector<std::weak_ptr<Entity> > getSubListResourceCollision();
    int getCurrentCellX() const;
    int getCurrentCellY() const;

    //setters
    void setMating();
    void setBrain(NeuralNetwork * newBrain);
    void setSex(bool sex);
    void setAge(int age) {m_age = age;}
    void setAngle(double angle) {m_angle = angle;}
    void setHunger(int hunger) {m_hunger = hunger;}
    void setThirst(int thirst) {m_thirst = thirst;}
    void setHealth(int health) {m_health = health;}
    void setScore(double score) {m_score = score;}

    //basic methods
    void die();
    void move(int speedPercentage);
    void turn(double angle);
    void drink();
    void eat();
    void mate();
    void attack();
    void evolve(NeuralNetwork *bestNN);
    void loseLive(unsigned liveToLose);
    void addEntityInListCollision(std::weak_ptr<Entity> e);
    void clearEntityListCollision();

    //game methods
    virtual int play();
    virtual void mappageInput();
    virtual void mappageOutput();

protected:
    virtual void tryToEat(std::shared_ptr<Entity> food);
    virtual bool tryToMate(std::shared_ptr<Entity> animalEntity);

    template <class Living> void reproduce(std::shared_ptr<Living> father);

    int m_health;
    int m_hunger;
    int m_thirst;
    bool m_female;
    int m_mating;
    double m_speed;
    double m_energy;
    double m_score;

private :
    int m_age;
    int m_maxSpeed;
    double m_damage;
    double m_angle; // m_angle in rad
    int m_fear;
    bool dead;
    double m_rotation;
    std::list<std::weak_ptr<Entity>> m_collisionList;
    NeuralNetwork* m_brain;
    std::vector<double> m_nnInputs;
    std::vector<double> m_nnOutputs;
    Vision * m_vision;
    World * m_world;

    //private methods

};



/////////////////////////////////////
///template definition:
/////////////////////////////////////

template <class Living>
void Animal::reproduce(std::shared_ptr<Living> father)
{
    // Use a normal distribution to determine the number of children of litter
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(config::MAX_CHILD_PER_ANIMAL/2, 1.5);
    int numberChild = (int)distribution(generator);

    // Normalize in the possible range
    if(numberChild < 0) numberChild = 0;
    else if(numberChild > config::MAX_CHILD_PER_ANIMAL) numberChild = config::MAX_CHILD_PER_ANIMAL;

    // Create the new entity around the mother (in a circle)
    int child = 0;
    double angleIntervalle = (2*PI)/(double)numberChild;
    double baseAngle = 0;
    double baseRadius = 4*getRadius();

    //cout << "FATHER BRAIN\n" << endl;
    //father->getBrain()->printNetwork();

    //cout << "MOTHER BRAIN\n" << endl;
    //this->getBrain()->printNetwork();

    std::uniform_real_distribution<double> distributionReal(-PI/6.0, PI/6.0);

    while(child < numberChild)
    {
        NeuralNetwork * childBrain = new NeuralNetwork( *(father->getBrain()), *m_brain  );
        //cout << "CHILD BRAIN\n" << endl;
        //childBrain->printNetwork();
        double distX = baseRadius*cos(baseAngle);
        double distY = baseRadius*sin(baseAngle);
        double magnitude = sqrt(distX*distX + distY*distY);
        double normalizeX = distX/magnitude;
        std::shared_ptr<Living> animal(std::make_shared<Living>(getX()+distX, getY()-distY, config::INITIAL_RADIUS, 50, 2, config::DEFAULT_ENERGY, m_world, childBrain) );
        double angleToTurn = acos(normalizeX);
        if(distY > 0) angleToTurn *= -1;
        animal->turn( angleToTurn + distributionReal(generator));
        m_world->addEntity(animal);
        baseAngle += angleIntervalle;
        child++;
    }
    m_mating = 0;
    father->setMating();
}

#endif // ANIMAL_H
