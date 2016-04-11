#ifndef MEAT_H
#define MEAT_H

#include "Resource.h"

class Meat : public Resource
{
public:
  Meat(int x, int y, int radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_MEAT; }
  int getNeralNetworkId() const { return NN_ID_MEAT; }
  int eat(int quantity);
};

#endif // MEAT_H
