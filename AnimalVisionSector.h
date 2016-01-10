#ifndef ANIMALVISIONSECTOR_H
#define ANIMALVISIONSECTOR_H

#include "Visionsector.h"
#include "Animal.h"

class AnimalVisionSector : public VisionSector
{
public:
    AnimalVisionSector(Coordinate &center, int leftAngle, int rightAngle, int range, bool frontSector, std::vector<Entity>& e);
    Animal scan();

private:
    bool m_frontSector;
};

#endif // ANIMALVISIONSECTOR_H
