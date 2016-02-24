#ifndef VISION_H
#define VISION_H

#include <vector>
using namespace std;

#include "Entity.h"
#include "Coordinate.h"
#include "Visionsector.h"

class Vision
{
	public:
	    Vision(const Coordinate * position, double * angle, vector<Entity*> &entities);
      virtual ~Vision();
      void see();
			vector<Percepted*> getPercepted();

	private:
        const Coordinate * m_position;
				const double * m_angle;
        vector<VisionSector *> m_sectors;
        vector<Entity*> &m_entities;
};

#endif // VISION_H
