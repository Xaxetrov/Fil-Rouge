#ifndef ANIMAL_H
#define ANIMAL_H

#include "Solid.h"
#include "World.h"
#include "NeuralNetwork.h"
#include "Vision.h"

class Animal : public Solid
{
public:
    //ctor, dtor
    Animal(double x, double y, int radius, int maxSpeed, World * world);
    ~Animal();

    //getters
    int getMaxSpeed() const;
    int getHealth() const;
    int getHunger() const;
    int getThirst() const;
    int getFear() const;
    double getAngle() const;
    const Vision * getVision() const;
    bool isDead() const;

    //basic methods
    void die();
    void move(int speedPercentage);
    void turn(double angle);

    //game methods
    virtual int play();
    virtual int computeScore();

    unsigned int getTypeId() { return 20; }


private :
    int m_maxSpeed;
    double m_angle; // m_angle in rad
    int m_health;
    int m_hunger;
    int m_thirst;
    int m_fear;
    bool dead;
    NeuralNetwork* m_brain;
    Vision * m_vision;
    World * m_world;
};

#endif // ANIMAL_H
