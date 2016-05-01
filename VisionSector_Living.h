#ifndef VISIONSECTOR_LIVING_H
#define VISIONSECTOR_LIVING_H

#include <memory>
#include <list>
#include "Visionsector.h"

class VisionSector_Living : public VisionSector
{
    public:
        VisionSector_Living(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, const int range, std::list<std::shared_ptr<Entity>> &entities);
        void see(const std::vector<std::shared_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities);

    private:

};

#endif // VISIONSECTOR_LIVING_H
