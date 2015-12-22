#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Entity.h"

class World
{
public:
    World();
    std::vector<Entity> & getEntities() {return m_entities;}

private:
    std::vector<Entity> m_entities;
};

#endif // WORLD_H
