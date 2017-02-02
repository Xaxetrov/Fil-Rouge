#ifndef PERCEPTED_H
#define PERCEPTED_H

#include <memory>
#include "Entity.h"

class Percepted
{
    public:
        Percepted(std::weak_ptr<Entity> entity, double distance, int max_range);
        Percepted();

        void set(std::weak_ptr<Entity> entity, double distance);

        const std::weak_ptr<Entity> getEntity() const { return m_entity; }
        double getDistance() const { return m_distance; }
        int getVisionRange() const {return m_maxVisionRange; }

    private:
        std::weak_ptr<Entity> m_entity;
        double m_distance;
        int m_maxVisionRange;
};

#endif // PERCEPTED_H
