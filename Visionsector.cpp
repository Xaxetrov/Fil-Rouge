#include "Visionsector.h"
#include "Percepted.h"
#include "Coordinate.h"

using namespace std;

#include <cstdlib>
#include <ctime>
#include <list>

VisionSector::VisionSector(const Coordinate &center, const double &animalAngle, const double &angle1, const double &angle2, int range,
                           std::list<std::shared_ptr<Entity>> &entities) :
    m_center(center), m_animalAngle(animalAngle), m_angle1(angle1), m_angle2(angle2), m_range(range), m_entities(entities)
{
    m_nearestPercepted = new Percepted();
}

VisionSector::~VisionSector()
{
    delete(m_nearestPercepted);
    clearPercepted();
}

void VisionSector::scan()
{
    std::vector<shared_ptr<Entity>> selection;
    std::vector<double> distances;

    for(shared_ptr<Entity> e:m_entities)
    {
        if(e->getX() == m_center.getX() && e->getY() == m_center.getY())
          continue;

        double d = Coordinate::getDistance(e->getCoordinate(), m_center);

        if(d < m_range)
        {
            selection.push_back(e);
            distances.push_back(d);
        }
    }

    clearPercepted();
    for(unsigned int i=0; i<selection.size(); i++)
    {
        shared_ptr<Entity> e = selection.at(i);
        double angle = Coordinate::getAngle(m_center, e->getCoordinate()) - m_animalAngle; // modulo2PI is moved insigned of getAngle

        if((angle <= m_angle1 && angle > m_angle2 && m_angle1 > m_angle2) || (angle >= m_angle1 && angle < m_angle2 && m_angle1 < m_angle2))
        {
            m_percepted.push_back(new Percepted(e, distances.at(i)));
        }
    }
}

void VisionSector::clearPercepted()
{
    m_percepted.clear();
}
