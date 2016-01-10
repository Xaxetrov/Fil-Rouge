#ifndef VISIONSECTOR_H
#define VISIONSECTOR_H

#include "Entity.h"
#include <vector>
#include <cmath>

class VisionSector
{
public:
    VisionSector(Coordinate &center, int leftAngle, int rightAngle, int range, std::vector<Entity>& e);
    void scan();

private :
    Coordinate &m_center;
    int m_leftAngle;
    int m_rightAngle;
    int m_range;
    std::vector<Entity>& m_entities;
    Entity* m_closest;
};

#endif // VISIONSECTOR_H
