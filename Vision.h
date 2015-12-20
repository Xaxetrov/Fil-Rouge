#ifndef VISION_H
#define VISION_H

#include <vector>

#include "VisionSector.h"

class Vision
{
public:
    Vision();

private :
    std::vector<VisionSector> sectors;
};

#endif // VISION_H
