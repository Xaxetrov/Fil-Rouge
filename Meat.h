#ifndef MEAT_H
#define MEAT_H

#include "Resource.h"

class Meat : public Resource
{
public:
  Meat(double x, double y, double radius, int quantity);
  Meat(Coordinate c, double radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_MEAT; }
  int getNeralNetworkId() const { return NN_ID_MEAT; }
  int eat(int quantity);
  bool isDead() const; //the meat don't grow on trees
};

#endif // MEAT_H
