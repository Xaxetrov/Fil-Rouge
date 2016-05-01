#ifndef VISION_H
#define VISION_H

#include <vector>
#include <list>

#include "Entity.h"
#include "Coordinate.h"
#include "Visionsector.h"

class Vision
{
public:
    Vision(const Coordinate & position, double & angle, std::list<std::shared_ptr<Entity>> &entities);
    virtual ~Vision();
    void see();
    std::vector<std::shared_ptr<Percepted>> getPercepted() const;

private:
    void scan();

    int m_maxRangeVision;
    std::vector<std::shared_ptr<Entity> > m_entitiesInRangeOfVision;
    std::vector<double> m_distanceOfEntities;
    const Coordinate & m_position;
    const double & m_angle;
    std::vector<VisionSector *> m_sectors;
    std::list<std::shared_ptr<Entity>> &m_entities;
};

#endif // VISION_H
