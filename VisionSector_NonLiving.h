#ifndef VISIONSECTOR_NONLIVING_H
#define VISIONSECTOR_NONLIVING_H

#include <memory>
#include <list>
#include "Visionsector.h"

class VisionSector_NonLiving : public VisionSector
{
    public:
        VisionSector_NonLiving(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range);
        void see(const std::vector<std::weak_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities);

    private:

};

#endif // VISIONSECTOR_NONLIVING_H
