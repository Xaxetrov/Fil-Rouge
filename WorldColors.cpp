#include "WorldColors.h"

#include <typeinfo>
#include "Animal.h"

WorldColors::WorldColors()
{
    backgroundBrush = QBrush(QColor(255,255,255));
    backgroundPen = QPen();
    waterBrush = QBrush(Qt::blue);
    waterPen = QPen(Qt::blue);
    grassBrush = QBrush(Qt::green);
    grassPen = QPen(Qt::green);

    teamsPen = QPen(Qt::black);
    teamsEye = QBrush(Qt::black);
    teamsBrushs.push_back(QBrush(Qt::darkGreen));
    teamsBrushs.push_back(QBrush(Qt::red));
    teamsBrushs.push_back(QBrush(Qt::cyan));
    teamsBrushs.push_back(QBrush(Qt::yellow));
}

QBrush & WorldColors::getEntityBrush(const Entity * entity)
{
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(typeid(*entity) == typeid( Animal ))
    {
        return teamsBrushs.at(2);
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundBrush;
}

QPen & WorldColors::getEntityPen(const Entity *entity)
{
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    if(typeid(*entity) == typeid( Animal ))
    {
        return teamsPen;
    }
    /*
    else if(typeid(entity) == typeid( ... ))
    {
    }
    [...]
    */
    return backgroundPen;
}

QBrush & WorldColors::getWaterBrush()
{
    return waterBrush;
}

QPen & WorldColors::getWaterPen()
{
    return waterPen;
}

QBrush & WorldColors::getGrassBrush()
{
    return grassBrush;
}

QPen & WorldColors::getGrassPen()
{
    return grassPen;
}

std::vector<QBrush> & WorldColors::getTeamsBrushs()
{
    return teamsBrushs;
}

QPen & WorldColors::getTeamsPen()
{
    return teamsPen;
}

QBrush & WorldColors::getBackgroundBrush()
{
    return backgroundBrush;
}

QBrush & WorldColors::getTeamsEyeBrush()
{
    return teamsEye;
}
