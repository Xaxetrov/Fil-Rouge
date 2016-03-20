#ifndef VEGETAL_H
#define VEGETAL_H

#include "Nonsolid.h"

class Vegetal : public NonSolid
{
public:
    Vegetal(int x, int y, int radius);
    virtual unsigned int getTypeId() const { return ID_VEGETAL; }

private:
    int m_quantity;
};

#endif //VEGETAL_H
