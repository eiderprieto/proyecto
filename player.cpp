#include "player.h"

float player::getVx() const
{
    return vx;
}

void player::setVx(float value)
{
    vx = value;
}

float player::getVy() const
{
    return vy;
}

void player::setVy(float value)
{
    vy = value;
}

float player::getCwidth() const
{
    return Cwidth;
}

void player::setCwidth(float value)
{
    Cwidth = value;
}

float player::getCheigh() const
{
    return Cheigh;
}

void player::setCheigh(float value)
{
    Cheigh = value;
}

float player::getPy() const
{
    return py;
}

void player::setPy(float value)
{
    py = value;
}

float player::getPx() const
{
    return px;
}

void player::setPx(float value)
{
    px = value;
}

float player::getAx() const
{
    return ax;
}

void player::setAx(float value)
{
    ax = value;
}

float player::getAy() const
{
    return ay;
}

void player::setAy(float value)
{
    ay = value;
}

float player::getWidth() const
{
    return width;
}

void player::setWidth(float value)
{
    width = value;
}

float player::getHeigh() const
{
    return heigh;
}

void player::setHeigh(float value)
{
    heigh = value;
}

float player::getDis() const
{
    return Dis;
}

void player::setDis(float value)
{
    Dis = value;
}

player::player(float _x, float _y, float _width, float _heigh)
{

    vx = 0;
    vy = 0;
    ax = 0;
    ay = g;

    imagen = QPixmap(":/imagenes/cuadrado.jpg");
    width = _width;
    heigh = _heigh;

    Cwidth = width/2.0;
    Cheigh = heigh/2.0;

    px = _x; py = _y;
    this->setPos(px,py);
}

QRectF player::boundingRect() const
{
    return QRectF(-Cwidth,-Cheigh,width,heigh);
}

void player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(boundingRect(),imagen,imagen.rect());

}

void player::aceleracion()
{
    ax = 0;
    ay = g;
}

void player::posicion()
{
    px = px + vx*dt + (ax*pow(dt,2))/2;
    py = py + vy*dt + (ay*pow(dt,2))/2;

    if(py >=500-Cheigh)
    {
        py = 500-Cheigh;
    }

    if(py<=-1000-Cheigh)
    {
        py = -1000-Cheigh;
    }

    if(px<=0+Cwidth)
    {
        px = Cwidth;
    }
   // this->setPos(px,py);
}

void player::velocidad()
{
    vx = vx + ax*dt;
    vy = vy + ay*dt;
}

void player::colision()
{
      if(px-(Cwidth/1.0)<=0.0)
        {
            vx = -e*vx;
            if(px-(Cwidth/1.0)<0.0)
            {
                px = (Cwidth/1.0)+1;
            }
        }
        if(px+(Cwidth/1.0)>=1000.0)
        {
            vx = -e*vx;
            if(px+(Cwidth/1.0)>1000.0)
            {
                px = 999-Cwidth/2;
            }
        }
        if(py+(Cheigh/1.0)>=500.0)
        {
            vy = -e*vy;
            if(py+(Cheigh/1.0)>500.0)
            {
                py = 499-Cheigh/1.0;
            }

        }
        if(py-(Cheigh/1.0)<=0.0)
        {
            vy = -e*vy;
            if(py-(Cheigh/1.0)<0.0)
            {
                py = Cheigh/1.0;
            }
        }
}

void player::mover()
{
    velocidad();
    posicion();

    this->setPos(px,py);
}

void player::detectarpiso(player *p, objetos *o)
{
    k = (o->getPy()-o->getCheigh())-(p->getPy()+p->getCheigh());
    if(-1.50<=k && k<1.5)
    {       p->setPos(p->getPx(),o->getPy()-o->getCheigh());
            p->setAy(0);
            p->setVy(0);

    }

}

void player::detectarChoque(player *p, objetos *o)
{
    Dis= abs((p->getPy()-p->getCheigh())-(o->getPy()+o->getCheigh()));
    R  = o->getPy()-p->getPy();// R es para Yw
    R2 = p->getCheigh()+o->getCheigh();
    D  = (o->getPx())-(p->getPx());// D es para x
    D2 = p->getCwidth()+o->getCwidth();

    if(R>0.0)
    {
        p->setAy(0);
        p->setVy(0);

    }
    else
    {
        if(Dis<=4.00)
        {
            R  = o->getPy()-p->getPy();
            py = py+4;
            p->setVy(200);
        }
        else
        {
            R  = o->getPy()-p->getPy();
            p->setVy(200);
        }
    }

    if(abs(D)-D2<=1.0)
    {
      if(((p->getPy()+p->getCheigh())-(o->getPy()-o->getCheigh()))<=1.0)
      {
          vx = vx;
      }
      else
      {
         if((abs(R)-R2)<=-1.4)
          vx = -vx*.9;
         else
             vx = vx;
      }
    }
}

