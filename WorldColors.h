#ifndef WORLDCOLORS_H
#define WORLDCOLORS_H

#include <memory>
#include <vector>
#include <QColor>
#include <QPen>

#include "Entity.h"

class WorldColors
{
public:
    WorldColors();

    QBrush getEntityBrush(const std::shared_ptr<Entity> entity);
    QPen   getEntityPen(const std::shared_ptr<Entity> entity);

    QBrush & getBackgroundBrush();
    QBrush & getWaterBrush();
    QPen & getWaterPen();
    QBrush & getGrassBrush();
    QPen & getGrassPen();
    QPen & getConnexionPen();
    std::vector<QBrush> & getTeamsBrushs();
    QPen & getTeamsPen();
    QBrush & getTeamsEyeBrush();

    QPen & getTeamsSelectedPen();

    QBrush setBrushAlpha(QBrush brush,int alpha) const;
    QPen   setPenAlpha(QPen pen,int alpha) const;

private:
    ///environnement colors: (non living)
    //Background color:
    QBrush backgroundBrush;
    QPen backgroundPen; //used in not found case
    //water color:
    QBrush waterBrush;
    QPen waterPen;
    //grass color:
    QBrush grassBrush;
    QPen grassPen;
    //meat color:
    QBrush meatBrush;
    QPen meatPen;
    QPen connexionPen;
    ///living colors:
    //teams colors:
    std::vector<QBrush> teamsBrushs;
    QPen teamsPen;
    QPen teamsSelectedPen;
    QBrush teamsEye;
    QBrush teamsNullBrush;
    QPen teamsNullPen;
};

#endif // WORLDCOLORS_H
