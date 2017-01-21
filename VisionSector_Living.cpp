#include "VisionSector_Living.h"
#include "Animal.h"

VisionSector_Living::VisionSector_Living(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range)
    : VisionSector(center, animalAngle, angle1, angle2, range)
{}

void VisionSector_Living::see(const std::vector<std::weak_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities)
{
    scan(entitiesInRangeOfVision, distanceOfEntities);

    double min = -1.0;
    std::shared_ptr<Percepted> indMin;
    for(std::shared_ptr<Percepted> p:m_percepted)
    {
        if(std::dynamic_pointer_cast<Animal>(p->getEntity()) != nullptr && (min == -1 || p->getDistance() < min))
        {
            indMin = p;
            min = p->getDistance();
        }
    }

    if(min == -1.0)
    {
        m_nearestPercepted->set(nullptr, 0);
    }
    else
    {
        m_nearestPercepted = indMin;
    }
}
