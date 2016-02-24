#ifndef VISIONSECTOR_H
#define VISIONSECTOR_H

#include <vector>
#include <cmath>
#include "Entity.h"
#include "Percepted.h"

class VisionSector
{
    public:
        VisionSector(const Coordinate * center, const double * animalAngle, const double angle1, const double angle2, int range, std::vector<Entity*> &entities);
        virtual ~VisionSector();

        virtual void see() = 0;
        const Percepted* getNearestPercepted() const { return m_nearestPercepted; }

    protected:
        void scan();

        std::vector<Percepted*> m_percepted;
        Percepted* m_nearestPercepted;

    private :
        void clearPercepted(); // Clear and free memory of m_percepted.

        const Coordinate * m_center;
        const double * m_animalAngle;
        double m_angle1;
        double m_angle2;
        int m_range;
        std::vector<Entity*>& m_entities;
};

#endif // VISIONSECTOR_H
