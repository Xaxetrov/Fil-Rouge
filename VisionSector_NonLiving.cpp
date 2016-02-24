#include "VisionSector_NonLiving.h"
#include "Animal.h"
#include <fstream>
using namespace std;

VisionSector_NonLiving::VisionSector_NonLiving(const Coordinate * center, double * animalAngle, const double angle1, const double angle2, int range, std::vector<Entity*> &entities): VisionSector(center, animalAngle, angle1, angle2, range, entities)
{}

void VisionSector_NonLiving::see()
{
    scan();

    double min = -1;
    int indMin = 0;

    for(unsigned int i = 0; i < m_percepted.size(); i++)
    {
        if(dynamic_cast <const Animal*> (m_percepted.at(i)->getEntity()) == nullptr && (min == -1 || m_percepted.at(i)->getDistance() < min))
        {
            indMin = i;
            min = m_percepted.at(i)->getDistance();
        }
    }

    if(min == -1)
    {
        m_nearestPercepted->set(nullptr, -1);
    }
    else
    {
        m_nearestPercepted = m_percepted.at(indMin);
    }
}
