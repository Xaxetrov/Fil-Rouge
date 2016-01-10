#ifndef VISION_H
#define VISION_H

#include <vector>

#include "Visionsector.h"

class Vision
{
public:
    Vision(Coordinate &center);

private :
    std::vector<VisionSector> sectors;
    Coordinate &m_center;
};

#endif // VISION_H
