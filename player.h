#ifndef PLAYER_H
#define PLAYER_H
#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <math.h>
#include <QPixmap>
#include <QTimer>
#include "objetos.h"

#define g 160
#define dt 0.006

class player : public QObject, public QGraphicsItem
{
  float px, py;
  float vx, vy;
  float ax, ay;
  float width, heigh;
  float Cwidth, Cheigh;
  float e = 1;
  float k,D,D2,R,R2,Dis;

  int  health = 1000;


  QPixmap imagen;

    Q_OBJECT
public:
   player(float _x, float _y,float _width, float _heigh);
   QRectF boundingRect() const;
   void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);



  // movimient's methods
   void aceleracion();
   void posicion();
   void velocidad();

   void colision();
   void mover();
  //end moviment's methods


   // get methods
   float getPx() const;
   float getPy() const;
   float getVx() const;
   float getVy() const;
   float getCheigh() const;
   float getCwidth() const;
   float getAx() const;
   float getAy() const;
   float getWidth() const;
   float getHeigh() const;
   float getDis() const;

   // set methods
   void setPx(float value);
   void setPy(float value);
   void setVx(float value);
   void setVy(float value);
   void setCwidth(float value);
   void setCheigh(float value);
   void setAx(float value);
   void setAy(float value);
   void setHeigh(float value);
   void setWidth(float value);
   void setDis(float value);

   void detectarpiso(player *p, objetos *o);
   void detectarChoque(player *p, objetos *o);








signals:

public slots:
};

#endif // PLAYER_H
