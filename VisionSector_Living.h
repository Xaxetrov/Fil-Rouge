#ifndef VISIONSECTOR_LIVING_H
#define VISIONSECTOR_LIVING_H

#include "Visionsector.h"

class VisionSector_Living : public VisionSector
{
    public:
        VisionSector_Living(Coordinate &center, int angle1, int angle2, int range, std::vector<Entity> &entities);
        bool see();

    private:
    
};

#endif // VISIONSECTOR_LIVING_H
