#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    Entity(int x, int y, int creationDate);
    int getX() {return m_x;}
    int getY() {return m_y;}
    int getCreationDate() {return m_creationDate;}

private:
    int m_x;
    int m_y;
    int m_creationDate;

};

#endif // ENTITY_H
