#include "VisionSector_Living.h"
#include "Animal.h"

VisionSector_Living::VisionSector_Living(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range)
    : VisionSector(center, animalAngle, angle1, angle2, range)
{}

void VisionSector_Living::see(const std::vector<std::weak_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities)
{
    scan(entitiesInRangeOfVision, distanceOfEntities);

    double distanceMin = -1.0;
    std::shared_ptr<Percepted> currentNearestPercepted;
    for(std::shared_ptr<Percepted> p:m_percepted)
    {
        std::weak_ptr<Entity> weakEntity = p->getEntity();
        if( std::shared_ptr<Entity> entity = weakEntity.lock() )
        {
            if(std::dynamic_pointer_cast<Animal>(entity) != nullptr && (distanceMin == -1.0 || p->getDistance() < distanceMin))
            {
                currentNearestPercepted = p;
                distanceMin = p->getDistance();
            }
        }
    }

    if(distanceMin == -1.0)
    {
        m_nearestPercepted = std::make_shared<Percepted>(std::weak_ptr<Entity>(), 0.0, getMaxRange()); //set nearestPercepted to null
    }
    else
    {
        m_nearestPercepted = currentNearestPercepted;
    }
}
