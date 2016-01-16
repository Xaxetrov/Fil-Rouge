#ifndef VISIONSECTOR_H
#define VISIONSECTOR_H

#include <vector>
#include <cmath>
#include "Entity.h"
#include "Percepted.h"

class VisionSector
{
    public:
        VisionSector(Coordinate &center, int angle1, int angle2, int range, std::vector<Entity> &entities);
        virtual ~VisionSector();

        virtual void see() = 0;
        Percepted* getNearestPercepted() { return m_nearestPercepted; };

    protected:
        void scan();

        std::vector<Percepted*> m_percepted;
        Percepted* m_nearestPercepted;

    private :
        void clearPercepted(); // Clear and free memory of m_percepted.

        Coordinate &m_center;
        int m_angle1;
        int m_angle2;
        int m_range;
        std::vector<Entity>& m_entities;
};

#endif // VISIONSECTOR_H
