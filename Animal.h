#ifndef ANIMAL_H
#define ANIMAL_H

#include <memory>
#include <list>

#include "Solid.h"
#include "World.h"
#include "NeuralNetwork.h"
#include "Vision.h"

class World;

class Animal : public Solid, public enable_shared_from_this<Animal>
{
public:
    //ctor, dtor
    Animal(double x, double y, int radius, int maxSpeed, double damage, World * world);
    Animal(double x, double y, int radius, int maxSpeed, double damage, World * world, NeuralNetwork * brain, int mating = 0);
    ~Animal();

    //getters
    int getMaxSpeed() const;
    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getFear() const;
    int getMating() const;
    double getDamage() const;
    double getAngle() const;
    const Vision * getVision() const;
    const NeuralNetwork * getBrain() const;
    bool isDead() const;
    bool isFemale() const;

    void setMating();

    //basic methods
    void die();
    void move(int speedPercentage);
    void turn(double angle);
    void drink();
    void mate();
    //virtual void eat();
    vector<weak_ptr<Entity> > getSubListCollision(unsigned int idEntity);
    void addEntityInListCollision(weak_ptr<Entity> e);

    //game methods
    virtual int play();
    virtual int computeScore();
    virtual void mappageInput();

    unsigned int getTypeId() const { return ID_ANIMAL; }


private :
    int m_maxSpeed;
    double m_damage;
    double m_angle; // m_angle in rad
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    int m_mating;
    bool dead;
    bool m_female;
    list<weak_ptr<Entity>> m_collisionList;
    NeuralNetwork* m_brain;
    std::vector<double> m_nnInputs;
    std::vector<double> m_nnOutputs;
    Vision * m_vision;
    World * m_world;

    //private methods
    void reproduce(shared_ptr<Animal> father);
};

#endif // ANIMAL_H
