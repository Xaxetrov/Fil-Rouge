#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Entity.h"

class World
{
public:
    World();
    std::vector<Entity*> & getEntities();

    Coordinate & getSize();
    int getSizeX() const;
    int getSizeY() const;
    bool isCollision(const Entity* e) const;

    void addEntity(Entity * entity);

private:
    bool isCollision(const Entity* e1, const Entity* e2) const;

    std::vector<Entity*> m_entities;
    Coordinate m_size;
};

#endif // WORLD_H
