#ifndef PERCEPTED_H
#define PERCEPTED_H

#include "Entity.h"

class Percepted
{
    public:
        Percepted(Entity *entity, double distance);
        Percepted();

        void set(Entity *entity, double distance);

        Entity * getEntity() { return m_entity; };
        double getDistance() { return m_distance; };

    private:
        Entity * m_entity;
        double m_distance;
};

#endif // PERCEPTED_H
