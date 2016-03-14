#ifndef WATER_H
#define WATER_H

#include "Nonsolid.h"

class Water : public NonSolid
{
public:
  Water(int x, int y, int radius);
  virtual unsigned int getTypeId() const { return 10; };
};


#endif // WATER_H
