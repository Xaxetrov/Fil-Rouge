#include "VisionSector_Living.h"
#include "Animal.h"

VisionSector_Living::VisionSector_Living(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range,
                                         std::vector<shared_ptr<Entity>> &entities):
    VisionSector(center, animalAngle, angle1, angle2, range, entities)
{}

void VisionSector_Living::see()
{
    scan();

    double min = -1;
    Percepted * indMin;
    for(Percepted * p:m_percepted)
    {
        if(dynamic_pointer_cast<Animal>(p->getEntity()) != nullptr && (min == -1 || p->getDistance() < min))
        {
            indMin = p;
            min = p->getDistance();
        }
    }

    if(min == -1)
    {
        m_nearestPercepted->set(nullptr, 0);
    }
    else
    {
        m_nearestPercepted = indMin;
    }
}
