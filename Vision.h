#ifndef VISION_H
#define VISION_H

#include <vector>

#include "Entity.h"
#include "Coordinate.h"
#include "Visionsector.h"

class Vision
{
	public:
	    Vision(Coordinate position, double angle, std::vector<Entity*> &entities);
        virtual ~Vision();
        void see();

	private:
        Coordinate m_position;
				int m_angle;
        std::vector<VisionSector *> m_sectors;
        std::vector<Entity*> &m_entities;
};

#endif // VISION_H
