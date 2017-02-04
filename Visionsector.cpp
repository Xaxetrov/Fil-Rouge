
#include "Visionsector.h"
#include "Percepted.h"
#include "Coordinate.h"

using namespace std;

#include <cstdlib>
#include <ctime>
#include <list>

VisionSector::VisionSector(const Coordinate &center, const double &animalAngle, const double &angle1, const double &angle2, int range) :
    m_center(center), m_animalAngle(animalAngle), m_angle1(angle1), m_angle2(angle2), m_range(range)
{
    m_nearestPercepted = std::make_shared<Percepted>();
}

VisionSector::~VisionSector()
{
    //delete(m_nearestPercepted);
    clearPercepted();
}

void VisionSector::scan(const std::vector<std::shared_ptr<Entity> > &entitiesInRangeOfVision, const std::vector<double> &distanceOfEntities)
{
    clearPercepted();
    for(unsigned int i=0; i<entitiesInRangeOfVision.size(); i++)
    {
        if (distanceOfEntities.at(i) < m_range)
        {
            shared_ptr<Entity> e = entitiesInRangeOfVision.at(i);
            double angle = Coordinate::getAngle(m_center, e->getCoordinate()) - m_animalAngle; // modulo2PI is moved insigned of getAngle

            if(angle >= m_angle1 && angle < m_angle2)
            {
                m_percepted.push_back(std::make_shared<Percepted>(e, distanceOfEntities.at(i), m_range));
            }
        }
    }
}

void VisionSector::clearPercepted()
{
    m_percepted.clear();
}
