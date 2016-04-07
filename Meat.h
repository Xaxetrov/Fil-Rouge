#ifndef MEAT_H
#define MEAT_H

#include "Resource.h"

class Meat : public Resource
{
public:
  Meat(int x, int y, int radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_MEAT; }
  void eat(int quantity);
};

#endif // MEAT_H
