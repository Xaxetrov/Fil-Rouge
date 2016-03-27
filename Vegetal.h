#ifndef VEGETAL_H
#define VEGETAL_H

#include "Resource.h"

class Vegetal : public Resource
{
public:
    Vegetal(int x, int y, int radius, int quantity);
    virtual unsigned int getTypeId() const { return ID_VEGETAL; }
    void eat(int quantity);

private:
};

#endif //VEGETAL_H
