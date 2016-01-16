#ifndef VISIONSECTOR_NONLIVING_H
#define VISIONSECTOR_NONLIVING_H

#include "Visionsector.h"

class VisionSector_NonLiving : public VisionSector
{
    public:
        VisionSector_NonLiving(Coordinate &center, int angle1, int angle2, int range, std::vector<Entity> &entities);
        bool see();

    private:

};

#endif // VISIONSECTOR_NONLIVING_H
