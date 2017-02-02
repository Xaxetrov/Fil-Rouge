#include "VisionSector_NonLiving.h"
#include "Animal.h"
#include <fstream>
using namespace std;

VisionSector_NonLiving::VisionSector_NonLiving(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range)
    : VisionSector(center, animalAngle, angle1, angle2, range)
{}

void VisionSector_NonLiving::see(const std::vector<std::weak_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities)
{
    scan(entitiesInRangeOfVision, distanceOfEntities);

    double currentMinDistance = -1.0;
    std::shared_ptr<Percepted> currentNearestPercepted;

    for(std::shared_ptr<Percepted> p:m_percepted)
    {
        std::weak_ptr<Entity> weakEntity = p->getEntity();
        if(std::shared_ptr<Entity> entity = weakEntity.lock())
        {
            if(dynamic_pointer_cast<Animal>(entity) == nullptr && (currentMinDistance == -1.0 || p->getDistance() < currentMinDistance))
            {
                currentNearestPercepted = p;
                currentMinDistance = p->getDistance();
            }
        }
    }

    if(currentMinDistance == -1.0)
    {
        m_nearestPercepted = std::make_shared<Percepted>(std::weak_ptr<Entity>(), 0.0, getMaxRange()); //set nearestPercepted to null
    }
    else
    {
        m_nearestPercepted = currentNearestPercepted;
    }
}
