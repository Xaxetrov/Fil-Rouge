#include "AnimalVisionSector.h"

AnimalVisionSector::AnimalVisionSector(Coordinate &center, int leftAngle, int rightAngle, int range, bool frontSector, std::vector<Entity>& e): VisionSector(center, leftAngle, rightAngle, range,e),
    m_frontSector(frontSector)
{

}

