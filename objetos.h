#ifndef OBJETOS_H
#define OBJETOS_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>

#define t 0.001

class objetos : public QObject, public QGraphicsItem
{
    float px, py;
    float width, heigh;
    float vx, vy;
    float Cwidth, Cheigh;

    QString imagen;
    QColor brush;


    Q_OBJECT
public:
    objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture,QColor _brush);
    objetos(float _x,float _y, float _width, float _heigh, QString picture,QColor _brush);
    objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture, QColor _brush, bool direc);


    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);


    void movBala();

    // get methods
    float getCwidth() const;
    float getCheigh() const;
    float getWidth() const;
    float getHeigh() const;
    float getPx() const;
    float getPy() const;
    float getVx() const;
    float getVy() const;

    //set methods
    void setCwidth(float value);
    void setCheigh(float value);
    void setWidth(float value);
    void setHeigh(float value);
    void setPx(float value);
    void setPy(float value);
    void setVx(float value);
    void setVy(float value);



signals:

public slots:
};

#endif // OBJETOS_H
