#include "VisionSector_NonLiving.h"
#include "Animal.h"
#include <fstream>
using namespace std;

VisionSector_NonLiving::VisionSector_NonLiving(const Coordinate & center, double & animalAngle, const double & angle1, const double & angle2, int range, std::list<shared_ptr<Entity>> &entities): VisionSector(center, animalAngle, angle1, angle2, range, entities)
{}

void VisionSector_NonLiving::see()
{
    scan();

    double min = -1;
    Percepted * indMin;
    for(Percepted * p:m_percepted)
    {
        if(dynamic_pointer_cast<Animal>(p->getEntity()) == nullptr && (min == -1 || p->getDistance() < min))
        {
            indMin = p;
            min = p->getDistance();
        }
    }

    if(min == -1)
    {
        m_nearestPercepted->set(nullptr, -1);
    }
    else
    {
        m_nearestPercepted = indMin;
    }
}
