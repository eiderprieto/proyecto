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

int objetos::getVidas() const
{
    return vidas;
}

void objetos::setVidas(int value)
{
    vidas = value;
}

bool objetos::getDireccion() const
{
    return direccion;
}

void objetos::setDireccion(bool value)
{
    direccion = value;
}


objetos::objetos(float _x, float _y, float _width, float _heigh, float _vx, QString picture, QColor _brush)
//enemigos
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
    aux1   = 1;


    this->setPos(px,py);
}

objetos::objetos(float _x, float _y, float _width, float _heigh, QString picture, QColor _brush)
//cosas y obsaculos
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
//balas
{
    py     = _y+5;
    if(direc==true)
    {
        vx = _vx;
        px = _x+45;

    }
    else
    {
        vx = -(_vx);
        px = _x-45;
    }
    frame = 3;
    frame1 = 1;
    timer = new QTimer();
    connect(timer,&QTimer::timeout,this,&objetos::sprites);
    timer->start(30);

    direccion = direc;

    width  = _width;
    heigh  = _heigh;
    Cwidth = width/2.0;
    Cheigh = heigh/2.0;
    imagen = picture;
    brush  = _brush;

    this->setPos(px,py);

}

void objetos::sprites()
{
    if(vx>0)
    {
        if(frame>4)
        {
            frame = 3;
        }
        imagen = ":/imagenes/balas 2.0/"+imagen.number(frame)+"c.png";
        frame++;
    }
    if(vx<0)
    {
        if(frame1>2)
        {
            frame1 = 1;
        }
        imagen = ":/imagenes/balas 2.0/"+imagen.number(frame1)+"c.png";
        frame1++;

    }
}

objetos::objetos(float pos_x, float pos_y, float _ancho, float _largo, float vel_x,float _rango,int _vidas,QString picture, QColor _brush)
//sprits enemigos
{
    width  = _ancho;
    heigh  = _largo;
    Cwidth = width/2.0;
    Cheigh = heigh/2.0;
    px     = pos_x;
    py     = pos_y;
    vx     = vel_x;
    imagen = picture;
    brush  = _brush;
    aux1   = 1;
    rango = _rango;
    vidas = _vidas;
    framer = 1;//izquierda
    framer1= 1;//derecha

    timer1 = new QTimer();
    connect(timer1,&QTimer::timeout,this,&objetos::spritesEnemigos);
    timer1->start(100);

    this->setPos(px,py);
}

objetos::objetos(float position_x, float position_y, float ancho_, float largo_)
//vidas
{
   width   = ancho_;
   heigh   = largo_;
   Cwidth  = width/2.0;
   Cheigh  = heigh/2.0;
   px      = position_x;
   py      = position_y;

   framer3 = 1;

   timer2 = new QTimer();
   connect(timer2,&QTimer::timeout,this,&objetos::spriteSalud);
   timer2->start(50);


   this->setPos(px,py);
}

objetos::objetos(float _posX, float _posY, float ancho, float largo, int consta)
//monedas
{

    width   = ancho;
    heigh   = largo;

    Cwidth  = width/2.0;
    Cheigh  = heigh/2.0;
    px      = _posX;
    py      = _posY;

    actual  = consta;
    timer3  = new QTimer();
    connect(timer3,&QTimer::timeout,this,&objetos::spriteMonedas);
    timer3->start(50);

    this->setPos(px,py);
}
void objetos::spriteSalud()
{
    imagen = ":/imagenes/vida/health"+imagen.number(framer3)+".png";
    framer3++;
    if(framer3>4)
    {
        framer3 = 1;
    }
}

void objetos::spriteMonedas()
{
    if(actual>9)
    {
        actual = 0;
    }
    imagen = ":/imagenes/monedas/"+imagen.number(actual)+".png";
    actual+=1;
}


void objetos::spritesEnemigos()
{

    if(vx<0)
    {
        if(framer>2)
        {
            framer = 1;
        }
        //:/imagenes/ratas 2.0/izquierda/nuevas ratas/1.png
        imagen = ":/imagenes/ratas 2.0/izquierda/nuevas ratas/"+imagen.number(framer)+".png";
        framer++;
    }
    if(vx>0)
    {
        //:/imagenes/ratas 2.0/derecha/nuevas ratas/1.png
        if(framer1>2)
        {
            framer1 = 1;
        }
        imagen = ":/imagenes/ratas 2.0/derecha/nuevas ratas/"+imagen.number(framer1)+".png";
        framer1++;

    }
}


QRectF objetos::boundingRect() const
{
    return QRectF(-Cwidth,-Cheigh,width,heigh);
}

void objetos::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPixmap pixmap;
    pixmap.load(imagen);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

void objetos::movBala()
{

    px = px + vx*dt1;
    this->setPos(px,py);
}

void objetos::moveEnemigos()
{
    if(aux1)
    {

        aux = px;
        aux1 =0;
    }
     if(px<aux-rango)
     {
         vx = -vx;
     }
     if(px>aux+rango)
     {
         vx = -vx;
     }

    px = px + vx*time;
    this->setPos(px,py);
}
