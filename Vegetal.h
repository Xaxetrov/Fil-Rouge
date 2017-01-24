#ifndef VEGETAL_H
#define VEGETAL_H

#include "Resource.h"

class Vegetal : public Resource
{
public:
    Vegetal(double x, double y, double radius, int quantity);
    virtual unsigned int getTypeId() const { return ID_VEGETAL; }
    int getNeuralNetworkId() const { return NN_ID_VEGETAL; }
    int eat(int quantity);

private:
};

#endif //VEGETAL_H
