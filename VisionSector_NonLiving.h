#ifndef VISIONSECTOR_NONLIVING_H
#define VISIONSECTOR_NONLIVING_H

#include "Visionsector.h"

class VisionSector_NonLiving : public VisionSector
{
    public:
        VisionSector_NonLiving(const Coordinate * center, double * animalAngle, const double angle1, const double angle2, int range, std::vector<Entity*> &entities);
        void see();

    private:

};

#endif // VISIONSECTOR_NONLIVING_H
