#ifndef MEAT_H
#define MEAT_H

#include "Resource.h"

class Meat : public Resource
{
public:
  Meat(int x, int y, int radius, int quantity);
  Meat(Coordinate c, int radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_MEAT; }
  int getNeralNetworkId() const { return NN_ID_MEAT; }
  int eat(int quantity);
  bool isDead() const{return m_quantity<=0;} //the meat don't grow on trees
};

#endif // MEAT_H
