#ifndef OBJETOS_H
#define OBJETOS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>


#define dt1 0.01
#define time 0.01

class objetos : public QObject, public QGraphicsItem
{
    float px, py;
    float width, heigh;
    float vx, vy;
    float Cwidth, Cheigh;
    float aux=0;
    float rango =0;
    int vidas =0;
    bool aux1 = 1;

    bool direccion = true;
    QTimer *timer;
    QTimer *timer1;
    QTimer *timer2;
    QTimer *timer3;

    QString imagen;
    QColor brush;
    //QPixmap imagen;
    //enteros de balas
    int frame;
    int frame1;

    //enteros de sprites enemigos
    int framer;
    int framer1;
    int framer3;

    float actual;



    Q_OBJECT
public:
    objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture,QColor _brush);
    objetos(float _x,float _y, float _width, float _heigh, QString picture,QColor _brush);
    objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture, QColor _brush, bool direc);
    objetos(float pos_x, float pos_y, float _ancho, float _largo, float vel_x, float _rango,int _vidas, QString picture, QColor _brush);
    objetos(float position_x,float position_y,float ancho_,float largo_);
    objetos(float _posX, float _posY,float ancho, float largo, int consta);

    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);


    void movBala();
    void moveEnemigos();

    // get methods
    float getCwidth() const;
    float getCheigh() const;
    float getWidth() const;
    float getHeigh() const;
    float getPx() const;
    float getPy() const;
    float getVx() const;
    float getVy() const;
    int getVidas() const;

    //set methods
    void setCwidth(float value);
    void setCheigh(float value);
    void setWidth(float value);
    void setHeigh(float value);
    void setPx(float value);
    void setPy(float value);
    void setVx(float value);
    void setVy(float value);
    void setVidas(int value);




    bool getDireccion() const;
    void setDireccion(bool value);

signals:

public slots:
    void sprites();
    void spritesEnemigos();
    void spriteSalud();
    void spriteMonedas();
};

#endif // OBJETOS_H
