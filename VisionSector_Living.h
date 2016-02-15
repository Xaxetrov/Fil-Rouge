#ifndef VISIONSECTOR_LIVING_H
#define VISIONSECTOR_LIVING_H

#include "Visionsector.h"

class VisionSector_Living : public VisionSector
{
    public:
        VisionSector_Living(Coordinate &center, const double animalAngle, const double angle1, const double angle2, const int range, std::vector<Entity*> &entities);
        void see();

    private:

};

#endif // VISIONSECTOR_LIVING_H
