#include "Vision.h"
#include "Coordinate.h"

Vision::Vision(Coordinate &position, std::vector<Entity> &entities) : m_position(&position), m_entities(entities)
{

}

