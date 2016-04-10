#ifndef WATER_H
#define WATER_H

#include "Resource.h"

class Water : public Resource
{
public:
  Water(int x, int y, int radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_WATER; }
  int getNeralNetworkId() const { return NN_ID_WATER; }

  void drink(int quantity);
};


#endif // WATER_H
