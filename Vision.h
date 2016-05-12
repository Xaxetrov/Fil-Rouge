#ifndef VISION_H
#define VISION_H

#include <vector>
#include <list>

#include "Entity.h"
#include "Coordinate.h"
#include "Visionsector.h"
#include "Animal.h"

class Animal;

typedef std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> gridOfEntities;

class Vision
{
public:
    Vision(const Animal & animal, double & angle, const std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> &gridOfEntities);
    virtual ~Vision();
    void see();
    std::vector<std::shared_ptr<Percepted>> getPercepted() const;

private:
    void scan();

    void getNeighbour(int cellX, int cellY, std::list<gridOfEntities&> rtn);

    int m_maxRangeVision;
    std::vector<std::shared_ptr<Entity> > m_entitiesInRangeOfVision;
    std::vector<double> m_distanceOfEntities;
    const Animal & m_animal;
    const double & m_angle;
    std::vector<VisionSector *> m_sectors;
    const std::vector<std::vector<std::list<std::shared_ptr<Entity>>>> & m_gridOfEntities;
};

#endif // VISION_H
