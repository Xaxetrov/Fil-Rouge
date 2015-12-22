#include "WorldColors.h"

#include <typeinfo>
#include "Animal.h"

WorldColors::WorldColors()
{
    backgroundBrush = QBrush(Qt::white);
    waterBrush = QBrush(Qt::blue);
    waterPen = QPen(Qt::blue);
    grassBrush = QBrush(Qt::green);
    grassPen = QPen(Qt::green);

    teamsPen = Qpen(Qt::black);
    teamsBrushs.push_back(QBrush(Qt::darkGreen));
    teamsBrushs.push_back(QBrush(Qt::red));
    teamsBrushs.push_back(QBrush(Qt::cyan));
    teamsBrushs.push_back(QBrush(Qt::yellow));
}

QBrush & WorldColors::getEntityBrush(Entity entity)
{
    switch(typeid(entity))
    {
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    default:
        return backgroundBrush;
    }
}

QPen & WorldColors::getEntityPen(Entity entity)
{
    switch(typeid(entity))
    {
    //TODO: complete with the corecte class name (don't existe when I wrote this)
    default:
        return QPen(Qt::NoPen);
    }
}

QBrush WorldColors::getWaterBrush()
{
    return waterBrush;
}

QPen WorldColors::getWaterPen()
{
    return waterPen;
}

QBrush WorldColors::getGrassBrush()
{
    return grassBrush;
}

QPen WorldColors::getGrassPen()
{
    return grassPen;
}

std::vector<QBrush> WorldColors::getTeamsBrushs()
{
    return teamsBrushs;
}

QPen WorldColors::getTeamsPen()
{
    return teamsPen;
}

QBrush WorldColors::getBackgroundBrush()
{
    return backgroundBrush;
}

