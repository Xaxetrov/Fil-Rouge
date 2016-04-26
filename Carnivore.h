#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "Animal.h"

class Carnivore : public Animal
{
public:
    Carnivore(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world);
    Carnivore(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, bool sex);
    Carnivore(double x, double y, int radius, int maxSpeed, double damage, double energy, World * world, NeuralNetwork * brain, int mating = 0);

    virtual unsigned int getTypeId() const { return ID_CARNIVORE; }
    virtual int getNeralNetworkId() const { return NN_ID_CARNIVORE; }

protected:
    virtual void tryToEat(std::shared_ptr<Entity> food);
    virtual bool tryToMate(std::shared_ptr<Entity> carnivoreEntity);
};

#endif // CARNIVORE_H
