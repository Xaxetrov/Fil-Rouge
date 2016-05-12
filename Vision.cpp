#include "config/config.h"
#include "Vision.h"
#include "VisionSector_Living.h"
#include "VisionSector_NonLiving.h"
#include "Coordinate.h"
using namespace std;

Vision::Vision(const Coordinate & position, double & angle, std::list<shared_ptr<Entity>> &entities) : m_position(position), m_angle(angle), m_entities(entities)
{
    int maxRangeVision = -1;
    for(int i = 0; i < NB_VISIONSECTORS_LIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_Living(m_position, angle, VISIONSECTORS_LIVING[i][0], VISIONSECTORS_LIVING[i][1], VISIONSECTORS_LIVING[i][2], entities)
        );
        if (maxRangeVision < VISIONSECTORS_LIVING[i][2])
            maxRangeVision = VISIONSECTORS_LIVING[i][2];
    }
    for(int i = 0; i < NB_VISIONSECTORS_NONLIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_NonLiving(m_position, angle, VISIONSECTORS_NONLIVING[i][0], VISIONSECTORS_NONLIVING[i][1], VISIONSECTORS_NONLIVING[i][2], entities)
        );
        if (maxRangeVision < VISIONSECTORS_NONLIVING[i][2])
            maxRangeVision = VISIONSECTORS_NONLIVING[i][2];
    }
    m_maxRangeVision = maxRangeVision;
}

Vision::~Vision()
{
    unsigned int size = m_sectors.size();
    for(unsigned int i = 0; i < size; i++)
    {
        delete(m_sectors[i]);
    }
}

void Vision::see()
{
    scan();
    for(unsigned int i = 0; i < m_sectors.size(); i++)
    {
        m_sectors.at(i)->see(m_entitiesInRangeOfVision, m_distanceOfEntities);
    }
}

vector<std::shared_ptr<Percepted>> Vision::getPercepted() const
{
  vector<std::shared_ptr<Percepted>> percepted;
  for(unsigned i=0 ; i < NB_VISIONSECTORS_LIVING + NB_VISIONSECTORS_NONLIVING; i++)
  {
      percepted.push_back(m_sectors[i]->getNearestPercepted());
  }
  return percepted;
}

void Vision::scan()
{
    m_entitiesInRangeOfVision.clear();
    m_distanceOfEntities.clear();

    for(shared_ptr<Entity> e : m_entities)
    {
        if(e->getX() == m_position.getX() && e->getY() == m_position.getY())
          continue;

        double distanceCarre = Coordinate::getDistanceCarre(e->getCoordinate(), m_position);

        if(distanceCarre < m_maxRangeVision * m_maxRangeVision)
        {
            m_entitiesInRangeOfVision.push_back(e);
            m_distanceOfEntities.push_back(sqrt(distanceCarre)); // sqrt is done as late as possible, to avoid doing it for all entities
        }
    }
}
