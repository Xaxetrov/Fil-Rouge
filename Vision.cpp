#include "config/config.h"
#include "Vision.h"
#include "VisionSector_Living.h"
#include "VisionSector_NonLiving.h"
#include "Coordinate.h"

Vision::Vision(const Animal & animal, double & angle, const std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> &gridOfEntities)
    : m_animal(animal), m_angle(angle), m_gridOfEntities(gridOfEntities)
{
    int maxRangeVision = -1;
    for(int i = 0; i < NB_VISIONSECTORS_LIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_Living(m_animal.getCoordinate(), angle, VISIONSECTORS_LIVING[i][0], VISIONSECTORS_LIVING[i][1], VISIONSECTORS_LIVING[i][2])
        );
        if (maxRangeVision < VISIONSECTORS_LIVING[i][2])
            maxRangeVision = VISIONSECTORS_LIVING[i][2];
    }
    for(int i = 0; i < NB_VISIONSECTORS_NONLIVING; i++)
    {
        m_sectors.push_back(
            new VisionSector_NonLiving(m_animal.getCoordinate(), angle, VISIONSECTORS_NONLIVING[i][0], VISIONSECTORS_NONLIVING[i][1], VISIONSECTORS_NONLIVING[i][2])
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

std::vector<std::shared_ptr<Percepted>> Vision::getPercepted() const
{
  std::vector<std::shared_ptr<Percepted>> percepted;
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
    int animalCellX = m_animal.getCurrentCellX();
    int animalCellY = m_animal.getCurrentCellY();

    World::mutexGridOfEntities.lock();
    unsigned int gridEntitySize1 = m_gridOfEntities.size();
    unsigned int gridEntitySize2 = m_gridOfEntities[0].size();
    World::mutexGridOfEntities.unlock();

    for (int i = -1; i <= 1; i++)
    {
        int currentCellX = (animalCellX + i + gridEntitySize1) % gridEntitySize1;
        for (int j = -1; j <= 1; j++)
        {
            int currentCellY = (animalCellY + j + gridEntitySize2) % gridEntitySize2;

            World::mutexGridOfEntities.lock();
            std::list<std::shared_ptr<Entity>> cell = m_gridOfEntities[currentCellX][currentCellY];
            World::mutexGridOfEntities.unlock();
            for(std::shared_ptr<Entity> e : cell)
            {
                if(e->getX() == m_animal.getX() && e->getY() == m_animal.getY())
                  continue;

                double distanceCarre = Coordinate::getDistanceCarre(e->getCoordinate(), m_animal.getCoordinate());

                if(distanceCarre < m_maxRangeVision * m_maxRangeVision)
                {
                    m_entitiesInRangeOfVision.push_back(e);
                    m_distanceOfEntities.push_back(sqrt(distanceCarre)); // sqrt is done as late as possible, to avoid doing it for all entities
                }
            }
        }
    }
}
