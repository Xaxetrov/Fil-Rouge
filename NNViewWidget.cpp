#include "NNViewWidget.h"
#include "config/config.h"

#include <iostream>

NNViewWidget::NNViewWidget(std::weak_ptr<Animal> a): QGraphicsView(), animal(a)
{
    setScene(&scene);
    updateView();
}

void NNViewWidget::updateView()
{
  std::shared_ptr<Animal> sharedAnimal = animal.lock();
  scene.clear();

  if(sharedAnimal)
  {
    QPen borderPen = colors.getEntityPen(sharedAnimal);
    QPen connexionPen = colors.getConnexionPen();
    QBrush & backgroundBrush = colors.getBackgroundBrush();

    // Draw connections
    for(unsigned int i = 1; i < NB_LAYERS; i++)
    {
      for(unsigned int j = 0; j < LAYER_SIZES[i]; j++)
      {
        //int x = (2*((j+1)%2)-1)*6*((j+1)/2) - 3*((LAYER_SIZES[i]%2)-1);
        int x = (LAYER_SIZES[i]/2) * (-6) - 3*((LAYER_SIZES[i]%2)-1) + 6 * j;
        int y = -20*i;

        std::vector<double> weights = sharedAnimal->getBrain()->getLayers().at(i-1).getNeurons().at(j).getWeights();
        std::vector<double> inputs = sharedAnimal->getBrain()->getLayers().at(i-1).getNeurons().at(j).getLastInputs();

        for(unsigned int k = 0; k < LAYER_SIZES[i-1]; k++)
        {
          if(inputs.size() == LAYER_SIZES[i-1])
          {
            double color;
            if(inputs[k] >= 0)
            {
              color = 171.0-171.0*inputs[k];
              if(color < 20)
                color = 20;
              else if(color > 171)
                color = 171;
              connexionPen.setBrush(QColor(171, color, color));
            }
            else
            {
              color = 171.0+140.0*inputs[k];
              if(color < 65)
                color = 65;
              else if(color > 171)
                color = 171;
              connexionPen.setBrush(QColor(color, color, 160));
            }
          }
          else
          {
            connexionPen.setBrush(QColor(171,171,171));
          }
          double width = 0.2 + 0.2*weights[k];
          if(width < 0.1)
            width = 0.1;
          connexionPen.setWidthF(width);

          QPolygonF connexion;
          connexion.push_back(QPoint(x, y));
          //connexion.push_back(QPoint((2*((k+1)%2)-1)*6*((k+1)/2) - 3*((LAYER_SIZES[i-1]%2)-1),-20*(i-1)));
          connexion.push_back(QPoint((LAYER_SIZES[i-1]/2) * (-6) - 3*((LAYER_SIZES[i-1]%2)-1) + 6 * k,-20*(i-1)));
          scene.addPolygon(connexion,connexionPen,backgroundBrush);
        }
      }
    }

    // Draw neurons
    for(unsigned int i = 0; i < NB_LAYERS; i++)
    {
      for(unsigned int j = 0; j < LAYER_SIZES[i]; j++)
      {
        //int x = (2*((j+1)%2)-1)*6*((j+1)/2) - 3*((LAYER_SIZES[i]%2)-1);
        int x = (LAYER_SIZES[i]/2) * (-6) - 3*((LAYER_SIZES[i]%2)-1) + 6 * j;
        int y = -20*i;

        double neuronActivation = 0;

        if(i > 0)
        {
          neuronActivation = sharedAnimal->getBrain()->getLayers().at(i-1).getNeurons().at(j).getLastOutput();
        }
        else if(NB_LAYERS >= 1 and sharedAnimal->getBrain()->getLayers().at(0).getNeurons().at(0).getLastInputs().size() == LAYER_SIZES[0])
        {
          neuronActivation = sharedAnimal->getBrain()->getLayers().at(0).getNeurons().at(0).getLastInputs().at(j);
        }

        QColor * neuronColor;
        if(neuronActivation >= 0)
        {
          double color = 171.0-171.0*neuronActivation;
          if(color < 20)
            color = 20;
          else if(color > 171)
            color = 171;
          neuronColor = new QColor(QColor(171, color, color));
        }
        else
        {
          double color = 171.0+140.0*neuronActivation;
          if(color < 65)
            color = 65;
          else if(color > 171)
            color = 171;
          neuronColor = new QColor(QColor(color, color, 160));
        }
        QRect baseSquare(x-1.5, y-1.8, 3, 3);
        scene.addEllipse(baseSquare,borderPen,*neuronColor);
        delete(neuronColor);
      }
    }
  }
}

void NNViewWidget::resizeEvent(QResizeEvent *e)
{
    this->fitInView(this->sceneRect(),Qt::KeepAspectRatio);
}

void NNViewWidget::setAnimal(std::weak_ptr<Animal> a)
{
    animal = a;
    updateView();
}
