#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "Animal.h"
#include "NeuralNetwork.h"

class World;

class Herbivore : public Animal
{
public:
    Herbivore(double x, double y, int radius, int maxSpeed, double damage, World * world);
    Herbivore(double x, double y, int radius, int maxSpeed, double damage, World * world, bool sex);
    Herbivore(double x, double y, int radius, int maxSpeed, double damage, World * world, NeuralNetwork * brain, int mating = 0);

    virtual unsigned int getTypeId() const { return ID_HERBIVORE; }
    virtual int getNeralNetworkId() const { return NN_ID_HERBIVORE; }

protected:
    virtual void tryToEat(std::shared_ptr<Entity> food);
    virtual bool tryToMate(std::shared_ptr<Entity> herbivoreEntity);


};

#endif // HERBIVORE_H
