#ifndef WATER_H
#define WATER_H

#include "Nonsolid.h"

class Water : public NonSolid
{
public:
  Water(int x, int y, int radius, int quantity);
  virtual unsigned int getTypeId() const { return ID_WATER; }

  int getQuantity() const;
  void drink(int quantity);
  virtual int play();

private:
  int m_quantity;
};


#endif // WATER_H
