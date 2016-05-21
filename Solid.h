#ifndef SOLID_H
#define SOLID_H

#include <mutex>
#include "Entity.h"

/* DEPRECATED CLASS -> TO REMOVE
 * A solid is an entity which is eligible to generate collisions
 */
class Solid : public Entity
{
public:
    //Ctor
    Solid(int x, int y, int radius, int creationDate=0);

    //game methods
    virtual int play(std::mutex * mutexEntities, std::mutex * mutexAttributes, std::mutex * mutexGridOfEntities, std::mutex * mutexListEntities, std::mutex * mutexCollisionList);
    /*
     * Called usually by a tick method. Overload to make your solid play
     */

};

#endif // SOLID_H
