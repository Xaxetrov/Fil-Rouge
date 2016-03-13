#include "Visionsector.h"
#include "Percepted.h"
#include "Coordinate.h"

using namespace std;

#include <cstdlib>
#include <ctime>

VisionSector::VisionSector(const Coordinate * center, const double * animalAngle, const double angle1, const double angle2, int range,
                           std::vector<Entity*>& entities) :
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
    std::vector<Entity*> selection;
    std::vector<double> distances;

    for(unsigned int i=0; i<m_entities.size(); i++)
    {
        if(m_entities.at(i)->getX() == m_center->getX() && m_entities.at(i)->getY() == m_center->getY())
          continue;

        double d = Coordinate::getDistance(Coordinate(m_entities.at(i)->getX(), m_entities.at(i)->getY()), Coordinate(m_center->getX(), m_center->getY()));

        if(d < m_range)
        {
            selection.push_back(m_entities.at(i));
            distances.push_back(d);
        }
    }

    clearPercepted();
    for(unsigned int i=0; i<selection.size(); i++)
    {
        int dX = selection.at(i)->getX();
        int dY = selection.at(i)->getY();
        double angle = Coordinate::modulo2PI(Coordinate::getAngle(*m_center, Coordinate(dX, dY)) - *m_animalAngle);

        if((angle <= m_angle1 && angle > m_angle2 && m_angle1 > m_angle2) || (angle >= m_angle1 && angle < m_angle2 && m_angle1 < m_angle2))
        {
            m_percepted.push_back(new Percepted(selection.at(i), distances.at(i)));
        }
    }
}

void VisionSector::clearPercepted()
{
    m_percepted.clear();
}
