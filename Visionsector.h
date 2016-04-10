#ifndef VISIONSECTOR_H
#define VISIONSECTOR_H

#include <memory>
#include <vector>
#include <list>
#include <cmath>
#include "Entity.h"
#include "Percepted.h"

class VisionSector
{
    public:
        VisionSector(const Coordinate & center, const double & animalAngle, const double & angle1, const double & angle2, int range, std::list<std::shared_ptr<Entity> > &entities);
        virtual ~VisionSector();

        virtual void see() = 0;
        std::shared_ptr<Percepted> getNearestPercepted() const { return m_nearestPercepted; }

    protected:
        void scan();

        std::vector<std::shared_ptr<Percepted>> m_percepted;
        std::shared_ptr<Percepted> m_nearestPercepted;

    private :
        void clearPercepted(); // Clear and free memory of m_percepted.

        const Coordinate & m_center;
        const double & m_animalAngle;
        double m_angle1;
        double m_angle2;
        int m_range;
        //shared_ptr that way a dead entity can still be seen if died just after vision
        std::list<std::shared_ptr<Entity>>& m_entities;
};

#endif // VISIONSECTOR_H
