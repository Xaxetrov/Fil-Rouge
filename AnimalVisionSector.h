#ifndef ANIMALVISIONSECTOR_H
#define ANIMALVISIONSECTOR_H

#include "VisionSector.h"
#include "Animal.h"

class AnimalVisionSector : public VisionSector
{
public:
    AnimalVisionSector(int leftAngle, int rightAngle, int range, bool frontSector);
    Animal scan();

private:
    bool m_frontSector;
};

#endif // ANIMALVISIONSECTOR_H
