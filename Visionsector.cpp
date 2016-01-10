#include "Visionsector.h"

VisionSector::VisionSector(Coordinate &center, int leftAngle, int rightAngle, int range, std::vector<Entity>& e) : m_center(center), m_leftAngle(leftAngle),
    m_rightAngle(rightAngle), m_range(range), m_entities(e), m_closest(nullptr)
{
}

void VisionSector::scan()
{
    std::vector<Entity*> selection;
    std::vector<double> distances;
    for(unsigned int i=0; i<m_entities.size(); i++)
    {
        double d = sqrt(pow(m_entities.at(i).getX()-m_center.getX(),2)+pow(m_entities.at(i).getY()-m_center.getY(),2));
        if(d<m_range)
        {
            selection.push_back(&m_entities.at(i));
            distances.push_back(d);
        }
    }

    std::vector<Entity*> selection2;
    std::vector<double> distances2;
    for(unsigned int i=0; i<selection.size(); i++)
    {
        int dX = selection.at(i)->getX();
        int dY = selection.at(i)->getY();
        double angle = atan2(dY,dX);
        if((angle<m_leftAngle && angle>m_rightAngle) || (angle>m_leftAngle && angle<m_rightAngle && m_leftAngle<m_rightAngle))
        {
            selection2.push_back(selection.at(i));
            distances2.push_back(distances.at(i));
        }
    }

    if(selection2.size()==0)
    {
        m_closest=nullptr;
    }
    else
    {
        double min=distances2[0];
        int indMin=0;
        for(unsigned int i=0; i<distances2.size();i++)
        {
            if(distances2.at(i)<min)
            {
                indMin=i;
                min=distances2.at(i)<min;
            }
        }
        m_closest=selection2.at(indMin);
    }
}
