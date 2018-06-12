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

#include <QString>

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

  int frame=0,frame1=5,estatico = 10,estatico1=9;


  QPixmap imagen;
  QString imagen1;
  QString Izquierda = ":/imagenes/jugador 2.0/izquierda/saltoizquierda.png";
  QString Derecha = ":/imagenes/jugador 2.0/derecha/saltoDerecha.png";

    Q_OBJECT
public:
   player(float _x, float _y,float _width, float _heigh,QString picture);

   QRectF boundingRect() const;
   void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);

   QTimer *timer;
   objetos *vista;

  // movimient's methods
   void aceleracion();
   void posicion();
   void posicionvs();
   void velocidad();

   void colision();
   void mover();
   void movervs();
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

   QPixmap getImagen() const;
   void setImagen(const QPixmap &value);

public slots:
   void sprites();
   void iniciar(void);






signals:

};

#endif // PLAYER_H
