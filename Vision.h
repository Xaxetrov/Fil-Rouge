#ifndef VISION_H
#define VISION_H

#include <vector>
#include <list>
using namespace std;

#include "Entity.h"
#include "Coordinate.h"
#include "Visionsector.h"

class Vision
{
public:
    Vision(const Coordinate & position, double & angle, list<shared_ptr<Entity>> &entities);
    virtual ~Vision();
    void see();
    vector<std::shared_ptr<Percepted>> getPercepted() const;

private:
    const Coordinate & m_position;
    const double & m_angle;
    vector<VisionSector *> m_sectors;
    list<shared_ptr<Entity>> &m_entities;
};

#endif // VISION_H
