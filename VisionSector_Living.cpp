#include "VisionSector_Living.h"
#include "Animal.h"

VisionSector_Living::VisionSector_Living(const Coordinate * center, double * animalAngle, const double angle1, const double angle2, int range, std::vector<Entity*> &entities): VisionSector(center, animalAngle, angle1, angle2, range, entities)
{}

void VisionSector_Living::see()
{
    scan();

    double min = -1;
    int indMin = 0;
    for(unsigned int i = 0; i < m_percepted.size(); i++)
    {
        if(dynamic_cast <Animal*> (m_percepted.at(i)->getEntity()) != nullptr && (min == -1 || m_percepted.at(i)->getDistance() < min))
        {
            indMin = i;
            min = m_percepted.at(i)->getDistance();
        }
    }

    if(min == -1)
    {
        m_nearestPercepted->set(nullptr, 0);
    }
    else
    {
        m_nearestPercepted = m_percepted.at(indMin);
    }
}
