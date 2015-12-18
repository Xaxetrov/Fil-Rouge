#ifndef VISIONSECTOR_H
#define VISIONSECTOR_H

#include "Entity.h"

class VisionSector
{
public:
    VisionSector(int leftAngle, int rightAngle, int range);

    //Entity scan();

private :
    int m_leftAngle;
    int m_rightAngle;
    int m_range;
};

#endif // VISIONSECTOR_H
