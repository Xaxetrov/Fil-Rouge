#ifndef ANIMAL_H
#define ANIMAL_H

#include "Solid.h"
#include "World.h"
#include "NeuralNetwork.h"
#include "Vision.h"

class World;

class Animal : public Solid
{
public:
    //ctor, dtor
    Animal(double x, double y, int radius, int maxSpeed, double damage, World * world);
    ~Animal();

    //getters
    int getMaxSpeed() const;
    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getFear() const;
    double getDamage() const;
    double getAngle() const;
    const Vision * getVision() const;
    bool isDead() const;

    //basic methods
    void die();
    void move(int speedPercentage);
    void turn(double angle);
    void drink();
    //virtual void eat();
    vector<Entity*> * getSubListCollision(unsigned int idEntity);
    void addEntityInListCollision(Entity* e);

    //game methods
    virtual int play();
    virtual int computeScore();


    unsigned int getTypeId() const { return ID_ANIMAL; }


private :
    int m_maxSpeed;
    double m_damage;
    double m_angle; // m_angle in rad
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    bool dead;
    vector<Entity*> * m_collisionList;
    NeuralNetwork* m_brain;
    Vision * m_vision;
    World * m_world;
};

#endif // ANIMAL_H
