#include "Vision.h"
#include "VisionSector_Living.h"
#include "VisionSector_NonLiving.h"
#include "Coordinate.h"
using namespace std;

Vision::Vision(const Coordinate & position, double & angle, std::list<shared_ptr<Entity>> &entities) : m_position(position), m_angle(angle), m_entities(entities)
{
    for(int i = 0; i < NB_VISIONSECTORS_LIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_Living(m_position, angle, VISIONSECTORS_LIVING[i][0], VISIONSECTORS_LIVING[i][1], VISIONSECTORS_LIVING[i][2], entities)
        );
    }
    for(int i = 0; i < NB_VISIONSECTORS_NONLIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_NonLiving(m_position, angle, VISIONSECTORS_NONLIVING[i][0], VISIONSECTORS_NONLIVING[i][1], VISIONSECTORS_NONLIVING[i][2], entities)
        );
    }
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
    for(unsigned int i = 0; i < m_sectors.size(); i++)
    {
        m_sectors.at(i)->see();
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
