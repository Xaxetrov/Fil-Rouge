#ifndef VISIONSECTOR_NONLIVING_H
#define VISIONSECTOR_NONLIVING_H

#include <memory>
#include <list>
#include "Visionsector.h"

class VisionSector_NonLiving : public VisionSector
{
    public:
        VisionSector_NonLiving(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range, std::list<std::shared_ptr<Entity>> &entities);
        void see();

    private:

};

#endif // VISIONSECTOR_NONLIVING_H
