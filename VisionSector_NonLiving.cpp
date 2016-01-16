#include "VisionSector_NonLiving.h"

VisionSector_NonLiving::VisionSector_NonLiving(Coordinate &center, int angle1, int angle2, int range, std::vector<Entity> &entities): VisionSector(center, angle1, angle2, range, entities)
{}

void VisionSector_NonLiving::see()
{
    scan();

    double min = -1;
    int indMin = 0;
    for(unsigned int i = 0; i < m_percepted.size(); i++)
    {
        if(!m_percepted.at(i)->getEntity()->isLiving() && (min == -1 || m_percepted.at(i)->getDistance() < min))
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
