#include "niveles.h"
#include "ui_niveles.h"



niveles::niveles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();

    scene->setSceneRect(0,0,1000,500);

    ui->graphicsView->setScene(scene);

    timer      = new QTimer();
    Tscene     = new QTimer();
    Taux       = new QTimer();
    Td         = new QTimer();
    Ta         = new QTimer();
    Tbalas     = new QTimer();

    mensaje = new QMessageBox();
    mensaje->setText("¿Do you Wanna save progress?");
    mensaje->setWindowTitle(" ");
    mensaje->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    mensaje->setStandardButtons(QMessageBox::Save|QMessageBox::Cancel);



    connect(Tscene,SIGNAL(timeout()),this,SLOT(upScene()));
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizacion()));
    connect(Taux,SIGNAL(timeout()),this,SLOT(Sumaux()));
    connect(Td,SIGNAL(timeout()),this,SLOT(CalCantidadD()));
    connect(Ta,SIGNAL(timeout()),this,SLOT(CalCantidadA()));
    connect(Tbalas,SIGNAL(timeout()),this,SLOT(moVbalas()));

    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer->start(2);
    Tscene->start(16);
    Taux->start(20);
    Tbalas->start(10);


}

niveles::~niveles()
{
    delete ui;
}

void niveles::objetosN1()
{
    cosas.append(new objetos(600,200,60,10,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(320,300,100,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(440,300,30,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(600,50,100,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(700,50,50,80,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(800,50,80,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(70,450,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(180,400,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(250,350,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1100,450,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1200,50,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1300,0,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1400,-50,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1500,450,500,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1600,-100,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1700,-150,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(1500,-200,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(950,100,50,20,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());
    cosas.append(new objetos(400,470,200,10,0,":/imagenes/rectangulo.jpg",Qt::red));
    scene->addItem(cosas.last());


    obstaculos.append(new objetos(800,470,100,100,":/imagenes/rectangulo.jpg",Qt::green));
    scene->addItem(obstaculos.last());
    obstaculos.append(new objetos(900,470,100,100,":/imagenes/rectangulo.jpg",Qt::green));
    scene->addItem(obstaculos.last());
    obstaculos.append(new objetos(800,270,500,40,":/imagenes/rectangulo.jpg",Qt::green));
    scene->addItem(obstaculos.last());


    QPen mypen(Qt::yellow);
    jugador = new player(700,200,50,70);
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
}

void niveles::objetosN2()
{

}

void niveles::objetosN3()
{

}

void niveles::objetosN4()
{

}

void niveles::objetosN5()
{

}

void niveles::objetosN6()
{

}

void niveles::objetosN7()
{

}

void niveles::objetosN8()
{

}

void niveles::objetosN9()
{

}

void niveles::actualizacion()
{
    for(int i=0;i< obstaculos.length();i++)
    {
        if(jugador->collidesWithItem(obstaculos.at(i)))
        {
            q2= abs((jugador->getPy()-jugador->getCheigh())-(obstaculos.at(i)->getPy()+obstaculos.at(i)->getCheigh()));
            if(!flag3)//es false cuando no se presiona w
            {
                banCoy = true;
                jugador->detectarChoque(jugador,obstaculos.at(i));
            }break;
        }
    }

    for(int i =0;i<cosas.length();++i)
    {
        h = cosas.at(i)->getPy()-cosas.at(i)->getCheigh()-(jugador->getPy()+jugador->getCheigh());
        if(cosas.at(i)->collidesWithItem(jugador))
        {
            if(h>=-1.50){
                if(!flag)
                {
                    banCcy = true;
                    jugador->detectarpiso(jugador,cosas.at(i));
                }
            }break;
        }
    }
    if(banCcy==false && banCoy==false)//condicional significa que los dos no estan colisionando
    {
        jugador->setAy(g);
    }
    else
    {
        jugador->setAy(0);
    }
    banCcy = banCoy = false;

    jugador->mover();

}

void niveles::upScene()
{
    x = jugador->getPx()-jugador->getCwidth()-300;
    y = jugador->getPy()+jugador->getCheigh()-250;
    scene->setSceneRect(x+cont,y,scene->width(),scene->height());
}

float niveles::CalCantidadD()
{

    if(cont<0)
        cont+=1;
    vderecha=true;
    return cont;
}
float niveles::CalCantidadA()
{
    if(cont>-400)
        cont-=1;
    vderecha=false;
    return cont;
}

bool niveles::Sumaux()
{
    if(flagDir == flagDirAnt)
    {
       m = false;
    }
    else
    {
       m =  true;
       flagDirAnt = flagDir;
    }
    return m;
}

void niveles::moVbalas()
{

    for(int i =0;i<balas.length();i++)
    {
        balas.at(i)->movBala();

        QList <QGraphicsItem *> colliding_items = balas.at(i)->collidingItems();
        for(int i=0;i<colliding_items.size();i++){
            if(typeid(*(colliding_items[i]))==typeid(objetos)){
                scene->removeItem(balas.at(i));
                balas.removeAt(i);
                return;
            }
        }
        if(balas.at(i)->getPx()>jugador->getPx()+700)
        {
            scene->removeItem(balas.at(i));
            balas.removeAt(i);

        }
        else if(balas.at(i)->getPx()<jugador->getPx()-800)
        {
            scene->removeItem(balas.at(i));
            balas.removeAt(i);
        }
    }

    if(balas.length()==0)
    {
        disbala = true;
        Tbalas->stop();
    }
}


void niveles::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_F1)
    {
        mensaje->show();

    }

    if(ev->key()==Qt::Key_F)
    {   if(disbala)
        {
          Tbalas->start(5);
          balas.append(new objetos(jugador->getPx(),jugador->getPy(),50,10,300,":/imagenes/rectangulo.jpg",Qt::black,vderecha));
          scene->addItem(balas.last());

          disbala = false;
        }
        if(abs(balas.last()->getPx()-jugador->getPx())>200)
        {
          balas.append(new objetos(jugador->getPx(),jugador->getPy(),50,10,300,":/imagenes/rectangulo.jpg",Qt::black,vderecha));
          scene->addItem(balas.last());
        }
    }

    if(ev->key()==Qt::Key_W)
    {
       if(jugador->getPy()==500-jugador->getCheigh()){
           jugador->setVy(-160);
       }

       for(int i =0;i<cosas.length();++i)
       {
           if(jugador->collidesWithItem(cosas.at(i)))
           {
              flag = true;

              jugador->setVy(-140);
              break;
           }
       }
       for(int i =obstaculos.length()-1;i>=0;i--)
       {
           if(jugador->collidesWithItem(obstaculos.at(i)))
           {
               if(q2<4.0)
               {
                   flag3 = false;
                   jugador->setVy(260);
               }
               else
               {
                   flag3 = true;
                   jugador->setVy(-140);
               }
           }
       }
    }

   else if(ev->key()==Qt::Key_S)
    {  
        flag = true;
        jugador->setVy(80);
    }

  else if(ev->key()==Qt::Key_D)
    {
        flag3 = false;
        Ta->stop();
        flagDir = 1;
        if(Sumaux())
        {
            if(cont>0)
            cont =0;
            Td->start(1);
        }
        jugador->setVx(200);

    }

    if(ev->key()==Qt::Key_A)
    {
        flag3 = false;
        Td->stop();
        flagDir = 0;
        if(Sumaux())
        {
            if(cont<-399)
            cont =0;
            Ta->start(1);
        }
        jugador->setVx(-200);
    }
}

void niveles::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A)
    {
        jugador->setVx(0);

    }
    if(ev->key()==Qt::Key_S)
    {
        flag = false;

    }
    if(ev->key()==Qt::Key_W)
    {   flag3 = false;
        flag = false;
    }
}

bool niveles::getFlag3() const
{
    return flag3;
}

void niveles::setFlag3(bool value)
{
    flag3 = value;
}

bool niveles::getFlag() const
{
    return flag;
}

void niveles::setFlag(bool value)
{
    flag = value;
}





