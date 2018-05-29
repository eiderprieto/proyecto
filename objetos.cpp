#include "objetos.h"

float objetos::getCwidth() const
{
    return Cwidth;
}

void objetos::setCwidth(float value)
{
    Cwidth = value;
}

float objetos::getCheigh() const
{
    return Cheigh;
}

void objetos::setCheigh(float value)
{
    Cheigh = value;
}

float objetos::getWidth() const
{
    return width;
}

void objetos::setWidth(float value)
{
    width = value;
}

float objetos::getHeigh() const
{
    return heigh;
}

void objetos::setHeigh(float value)
{
    heigh = value;
}

float objetos::getPx() const
{
    return px;
}

void objetos::setPx(float value)
{
    px = value;
}

float objetos::getPy() const
{
    return py;
}

void objetos::setPy(float value)
{
    py = value;
}

float objetos::getVx() const
{
    return vx;
}

void objetos::setVx(float value)
{
    vx = value;
}

float objetos::getVy() const
{
    return vy;
}

void objetos::setVy(float value)
{
    vy = value;
}

objetos::objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture, QColor _brush)
{
    width  = _width;
    heigh  = _heigh;
    Cwidth = width/2.0;
    Cheigh = heigh/2.0;
    px     = _x;
    py     = _y;
    vx     = _vx;
    imagen = picture;
    brush  = _brush;
    this->setPos(px,py);
}

objetos::objetos(float _x, float _y, float _width, float _heigh, QString picture, QColor _brush)
{
    width  = _width;
    heigh  = _heigh;
    Cwidth = width/2.0;
    Cheigh = heigh/2.0;
    px     = _x;
    py     = _y;
    imagen = picture;
    brush  = _brush;
    this->setPos(px,py);
}

objetos::objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture, QColor _brush, bool direc)
{
    px     = _x;
    py     = _y;
    if(direc==true)
    {
        vx = _vx;

    }
    else
    {
        vx = -(_vx);
    }

    width  = _width;
    heigh  = _heigh;
    Cwidth = width/2.0;
    Cheigh = heigh/2.0;
    imagen = picture;
    brush  = _brush;

    this->setPos(px,py);

}



QRectF objetos::boundingRect() const
{
    return QRectF(-Cwidth,-Cheigh,width,heigh);
}

void objetos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRectF rec = boundingRect();
    //painter->drawPixmap(boundingRect(),imagen,imagen.rect());
    QBrush brusher(brush);
    if(scene()->collidingItems(this).isEmpty())
    {
        brusher.setColor(brush);
    }
    else
    {
        brusher.setColor(Qt::yellow);
    }
    painter->fillRect(rec,brusher);
    painter->drawRect(rec);
}

void objetos::movBala()
{
    px = px + vx*t;
    this->setPos(px,py);
}
