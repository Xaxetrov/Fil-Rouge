#ifndef PERCEPTED_H
#define PERCEPTED_H

#include <memory>
#include "Entity.h"

class Percepted
{
    public:
        Percepted(std::shared_ptr<Entity> entity, double distance);
        Percepted();

        void set(std::shared_ptr<Entity> entity, double distance);

        const std::shared_ptr<Entity> getEntity() const { return m_entity; }
        double getDistance() const { return m_distance; }

    private:
        std::shared_ptr<Entity> m_entity;
        double m_distance;
};

#endif // PERCEPTED_H
