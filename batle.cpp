#include "batle.h"
#include "ui_batle.h"

batle::batle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::batle)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1300,700);
    ui->graphicsView->setScene(scene);
    Tbalas1=new QTimer();
    Tbalas2=new QTimer();
    Pjugador=new QTimer();
    connect(Tbalas1,SIGNAL(timeout()),this,SLOT(movebalas1()));
    connect(Pjugador,SIGNAL(timeout()),this,SLOT(actualizacion()));
    connect(Tbalas2,SIGNAL(timeout()),this,SLOT(movebalas2()));
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
    ui->graphicsView->setStyleSheet("background: white");

    //fondo de la escena.........................................
    /**/  QPixmap brusher(":/imagenes/escenarios/alcantarilla.png");
    /**/  QGraphicsPixmapItem *item = scene->addPixmap(brusher);
    /**/  item->setPos(0,0);
    /**/  scene->addPixmap(brusher)->setPos(0,0);
    //fin del fondo de la escena.................................




    Tbalas1->start(10);//timer del slot movbala1
    Tbalas2->start(10);//timer del slot movbala1
    Pjugador->start(10);//timer del lot actualizacion

    obstaculos.append(new objetos(-400,350,800,700,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    scene->addItem(obstaculos.last());//Izquierda
    obstaculos.append(new objetos(1700,350,800,700,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    scene->addItem(obstaculos.last());//Derecha
    obstaculos.append(new objetos(650,25,1300,50,":/imagenes/escenarios/bordes.jpg",Qt::transparent));
    scene->addItem(obstaculos.last());//Arriba
//    obstaculos.append(new objetos(900,650,1800,300,":/imagenes/rectangulo.jpg",Qt::darkBlue));
//    scene->addItem(obstaculos.last());//Abajo

    //vidas jugador 1
    for(int i=0;i<10;i++)
    {
        vidas1.append(new objetos(50+(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
        scene->addItem(vidas1.last());
    }

    //vidas jugador 2
    for(int i=0;i<10;i++)
    {
        vidas2.append(new objetos(1275-(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
        scene->addItem(vidas2.last());
    }
    reinicio=0;

    izquierda1 =true;//boleao de dreccion del disparo jugador1
    izquierda2 =false;//boleao de dreccion del disparo jugador2
    disbala1   =true; // boleano que permite disparar la primera bala luego de que el vector se vacie y no genere errores
    disbala2   =true; // boleano que permite disparar la primera bala luego de que el vector se vacie y no genere errores
    flag3      =true; // bandera que permite detectar la colision con los objetos del primer jugador(obstaculos)
    flag       =true; // bandera que permite detectar la colision con los objetos del primer jugador(cosas)
    flag32     =true; // bandera que permite detectar la colision con los objetos del segundo jugador(obstaculos)
    flag2      =true;
}

batle::~batle()//destructor
{
    delete ui;
}
void batle::movebalas1()//se quita las vidas de jugador 2 y se revisa que se pueda disparar
{

    if(balas1.isEmpty())//verificamos que se pueda disparar
    {
        disbala1 = true;
    }
    for(int i =0;i<balas1.length();i++)//se recorre el Qlist de balas del jugador
    {
        cont ++;
        balas1.at(i)->movBala();//se meve el objeto balas 1de la lista de balas[1]
        QList <QGraphicsItem *> colliding_items = balas1.at(i)->collidingItems();//e cra na lista de objetos colisionando
        for(int j=0;j<colliding_items.size();j++){//se recorre la lista
            if(typeid(*(colliding_items[j]))==typeid(objetos)||typeid(*(colliding_items[j]))==typeid(player)){//se verifica si el tipo de colisico s objeto a objeto o jugador objeto
                if(typeid(*(colliding_items[j]))==typeid(objetos))//si es tipo colision obeto a objeto
                {
                    scene->removeItem(balas1.at(j));//solo elmina la bala de la ecena
                    balas1.removeOne(balas1.at(j));//se elimina del vector
                }
                if(balas1.isEmpty())//se verifica si el vctr balas esa vacio (machetazo)
                {
                    balas1.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));//(se crea una bala en la porra para que el vector o este vacio
                    scene->addItem(balas1.last());//se agrega a la scena para que no salga el error
                }
                if(!vidas2.isEmpty())//se verifica que el jugador tenga vidas aun
                {

                    if(typeid(*(colliding_items[j]))==typeid(player))//se comprueba si es colision objeto jugador
                    {
                        scene->removeItem(balas1.at(j));//remueve la bala de la escena
                        balas1.removeOne(balas1.at(j));
                        scene->removeItem(vidas2.at(vidas2.length()-1));//remueve una vida del jugador 2
                        vidas2.removeAt(vidas2.length()-1);
                        if(balas1.isEmpty())//Machetazo
                        {
                            balas1.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                            scene->addItem(balas1.last());
                        }
                    }
                }
                return;
            }
        }

    }
    if(vidas2.length()==0)//se verifica si el asalto termino
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,//se envia mennsaje  a los jugadores
                                       "GANADOR JUGADOR 1", "Deseas volver a perder?",
                              QMessageBox::Yes | QMessageBox::No);//se recibe respuesta
        if(reply == QMessageBox::Yes)//se acepta el reinicio
        {
            reinicio=1;//es un entero, no podia ser booleno hubo el error ya que siempre reiniciaba o no entraba
            //QApplication::quit();
        }
        if(reply ==QMessageBox::No)//sale al menu principal
        {
            reinicio=2;
        }

        if(reinicio==1)//se entra a la opcion
        {
            while(!balas1.isEmpty())//elimina las balas restantes de la escena
            {
                scene->removeItem(balas1.last());
                balas1.removeLast();
            }
            while(!vidas1.isEmpty())//elimina las vidas del jugador 1 (ganador)
            {
                scene->removeItem(vidas1.last());
                vidas1.removeLast();
            }
           batle *batalla = new batle();//se crea un nuevo ui que se podra eliminar luego y reemplazarlo con otro ui
           batalla->deleteLater();
           batalla->additems();
           batalla->show();
           //remueve los jugadre de la escena anterior
           scene->removeItem(players.last());
           players.removeLast();
           scene->removeItem(players.last());
           players.removeLast();
           //-----------------------
           //se crean y se agregan a la escena los nuevos jugadores
           players.append(new player(25,665,50,70,":/imagenes/cuadrado.jpg"));
           players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/derecha/4.png"));
           scene->addItem(players.last());
           players.append(new player(1275,665,50,70,":/imagenes/cuadrado.jpg"));
           players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/izquierda/8.png"));
           scene->addItem(players.last());
           //-----------------------
           //vidas jugadores
           for(int i=0;i<10;i++)
           {
               vidas1.append(new objetos(50+(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
               scene->addItem(vidas1.last());
           }
           for(int i=0;i<10;i++)
           {
                vidas2.append(new objetos(1275-(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
                scene->addItem(vidas2.last());
           }
           //------------------------
        }

    }//vuelve  menu principal
    if(reinicio==2)
    {
        opciones *volver = new opciones();
        volver->show();
        delete this;
    }

}

void batle::movebalas2()
{
    if(balas2.isEmpty())
    {
        disbala2 = true;
    }
    for(int i =0;i<balas2.length();i++)
    {
        balas2.at(i)->movBala();
        QList <QGraphicsItem *> colliding_items = balas2.at(i)->collidingItems();
        for(int j=0;j<colliding_items.size();j++){
            if(typeid(*(colliding_items[j]))==typeid(objetos)||typeid(*(colliding_items[j]))==typeid(player)){
                if(typeid(*(colliding_items[j]))==typeid(objetos))
                {
                    scene->removeItem(balas2.at(j));
                    balas2.removeOne(balas2.at(j));
                }
                if(balas2.isEmpty())
                {
                    balas2.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                    scene->addItem(balas2.last());
                }
                if(!vidas1.isEmpty())
                {
                    if(typeid(*(colliding_items[j]))==typeid(player))
                    {
                        scene->removeItem(balas2.at(j));
                        balas2.removeOne(balas2.at(j));
                        scene->removeItem(vidas1.at(vidas1.length()-1));
                        vidas1.removeAt(vidas1.length()-1);
                        if(balas2.isEmpty())
                        {
                            balas2.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                            scene->addItem(balas2.last());
                        }
                    }
                }

                return;
            }
        }

    }
    if(vidas1.isEmpty())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                       "GANADOR JUGADOR 2", "Deseas volver a perder?",
                              QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            reinicio=1;
            //QApplication::quit();
        }
        if(reply ==QMessageBox::No)
        {
            reinicio=2;
        }

        if(reinicio==1)
        {
            while(!balas2.isEmpty())
            {
                scene->removeItem(balas2.last());
                balas2.removeLast();
            }
            while(!vidas2.isEmpty())
            {
                scene->removeItem(vidas2.last());
                vidas2.removeLast();
            }
           //Tbalas1->stop();

           batle *batalla = new batle();
           batalla->deleteLater();
           batalla->additems();
           batalla->show();

           scene->removeItem(players.last());
           players.removeLast();
           scene->removeItem(players.last());
           players.removeLast();

           players.append(new player(25,665,50,70,":/imagenes/cuadrado.jpg"));
           players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/derecha/4.png"));
           scene->addItem(players.last());
           players.append(new player(1275,665,50,70,":/imagenes/cuadrado.jpg"));
           players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/izquierda/8.png"));
           scene->addItem(players.last());
           //vidas jugador
           for(int i=0;i<10;i++)
           {
               vidas1.append(new objetos(50+(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
               scene->addItem(vidas1.last());
           }
           for(int i=0;i<10;i++)
           {
               vidas2.append(new objetos(1275-(i*30)-15,25,30,20,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::magenta));
               scene->addItem(vidas2.last());
           }


        }

    }
    if(reinicio==2)
    {
        opciones *volver = new opciones();
        volver->show();
        delete this;
    }

}


void batle::actualizacion()
{   
    //ACTUALIZACION DEL JUGADOR 1
    for(int i=0;i< obstaculos.length();i++)//se recorre la lista de obstaculos
    {
        if(players.at(0)->collidesWithItem(obstaculos.at(i)))//se verifica si el jugador colisionacom obstaculos
        {
            q2= abs((players.at(0)->getPy()-players.at(0)->getCheigh())-(obstaculos.at(i)->getPy()+obstaculos.at(i)->getCheigh()));
            if(!flag3)//es false cuando no se presiona w
            {
                banCoy = true;
                players.at(0)->detectarChoque(players.at(0),obstaculos.at(i));//verifica en que direccion colisiona arriba,abajo ,izquida,derecha
            }//break;
        }
    }
    for(int i =0;i<cosas.length();++i)//recorre el vector de cosas
    {
        h = cosas.at(i)->getPy()-cosas.at(i)->getCheigh()-(players.at(0)->getPy()+players.at(0)->getCheigh());
        //obtene el valor de h(arriba) que el val de si colisiona on el jugador
        if(cosas.at(i)->collidesWithItem(players.at(0)))//verifica si colisona con el jugador
        {
            if(h>=-1.50){//verifica el valo de h
                if(!flag)
                {
                    banCcy = true;//se activa bandera que no perite que el jugador caiga
                    players.at(0)->detectarpiso(players.at(0),cosas.at(i));//el jugador detecta el piso

                }
            }//break;
        }
    }
    if(banCcy==false && banCoy==false)//condicional significa que los dos no estan colisionando
    {
        players.at(0)->setAy(g);
    }
    else
    {
        players.at(0)->setAy(0);
    }
    banCcy = banCoy = false;
    //FIN DE LA ACTUALIZACION DEL JUGADOR 1

    //ACTUAIZACION DEL JUGADOR 2
    for(int i=0;i< obstaculos.length();i++)
    {
        if(players.at(1)->collidesWithItem(obstaculos.at(i)))
        {
            q22= abs((players.at(1)->getPy()-players.at(1)->getCheigh())-(obstaculos.at(i)->getPy()+obstaculos.at(i)->getCheigh()));
            if(!flag32)//es false cuando no se presiona w
            {
                banCoy2 = true;
                players.at(1)->detectarChoque(players.at(1),obstaculos.at(i));
            }//break;
        }
    }

    for(int i =0;i<cosas.length();++i)
    {
        h2 = cosas.at(i)->getPy()-cosas.at(i)->getCheigh()-(players.at(1)->getPy()+players.at(1)->getCheigh());

        if(cosas.at(i)->collidesWithItem(players.at(1)))
        {
            if(h2>=-1.50){
                if(!flag2)
                {
                    banCcy2 = true;
                    players.at(1)->detectarpiso(players.at(1),cosas.at(i));

                }
            }//break;
        }
    }
    if(banCcy2==false && banCoy2==false)//condicional significa que los dos no estan colisionando
    {
        players.at(1)->setAy(g);
    }
    else
    {
        players.at(1)->setAy(0);
    }
    banCcy2 = banCoy2 = false;


    //FIN DE LA ACTUALIZACION DEL JUGADOR 2

    for(int i =0;i<players.length();i++)
    {
        players.at(i)->movervs();
    }

}


void batle::additems()
{
    int i=filasb;int j=0;
    QFile archivos(":/documentos/batalla1.txt");
    int i1=filasb;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,700-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,700-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }


                if(j1==columnasb-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }

    players.append(new player(25,665,50,70,":/imagenes/cuadrado.jpg"));
    players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/derecha/4.png"));
    scene->addItem(players.last());
    players.append(new player(1275,665,50,70,":/imagenes/cuadrado.jpg"));
    players.last()->setImagen(QPixmap(":/imagenes/jugador 2.0/izquierda/8.png"));
    scene->addItem(players.last());
    ui->graphicsView->setFocus();

}


void batle::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_F1)
    {
        opciones *volver = new opciones();
        volver->show();
        delete this;

    }
    if(ev->key()==Qt::Key_F2)

    {
        delete this;
    }

    //teclas jugador 1************************************************""
    if(ev->key()==Qt::Key_J)
    {
        if(disbala1)
        {
            balas1.append(new objetos(players.at(0)->getPx(),players.at(0)->getPy(),40,10,300,":/imagenes/rectangulo1.jpg",Qt::black,izquierda1));
            scene->addItem(balas1.last());

            disbala1 = false;
        }
        if(abs(balas1.last()->getPx()-players.at(0)->getPx())>150)
        {
            balas1.append(new objetos(players.at(0)->getPx(),players.at(0)->getPy(),40,10,300,":/imagenes/rectangulo1.jpg",Qt::black,izquierda1));
            scene->addItem(balas1.last());
        }

    }

    if(ev->key()==Qt::Key_A)
    {
         flag3 = false;//
        izquierda1 = false;
        players.at(0)->setVx(-200);
    }
    if(ev->key()==Qt::Key_D)
    {
         flag3 = false;
          players.at(0)->setVx(200);
        izquierda1 = true;
    }
    if(ev->key()==Qt::Key_W)//salta
    {
       if(players.at(0)->getPy()==700-players.at(0)->getCheigh()){//verifica si esta en el piso, coordenadas
           players.at(0)->setVy(-260);
       }

       for(int i =0;i<cosas.length();++i)//verifica si colisionacon cosas
       {
           if(players.at(0)->collidesWithItem(cosas.at(i)))
           {
              flag = true;

              players.at(0)->setVy(-260);
              break;
           }
       }
       for(int i =obstaculos.length()-1;i>=0;i--)//verifica si colisiona con obstaculos
       {
           if(players.at(0)->collidesWithItem(obstaculos.at(i)))
           {
               if(q2<4.0)
               {
                   flag3 = false;
                   players.at(0)->setVy(260);
               }
               else
               {
                   flag3 = true;
                   players.at(0)->setVy(-260);
               }
           }
       }
    }

    if(ev->key()==Qt::Key_S)
    {
        flag = true;
        players.at(0)->setVy(180);
    }
    //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB""
    //teclas jugador 2**********************************************""
    if(ev->key()==Qt::Key_Space)
    {
        if(disbala2)
        {
            balas2.append(new objetos(players.at(1)->getPx(),players.at(1)->getPy(),40,10,300,":/imagenes/rectangulo1.jpg",Qt::black,izquierda2));
            scene->addItem(balas2.last());

            disbala2 = false;
        }
        if(abs(balas2.last()->getPx()-players.at(1)->getPx())>150)
        {
            balas2.append(new objetos(players.at(1)->getPx(),players.at(1)->getPy(),40,10,300,":/imagenes/rectangulo1.jpg",Qt::black,izquierda2));
            scene->addItem(balas2.last());
        }

    }

    if(ev->key()==Qt::Key_4)
    {
         flag32 = false;
        izquierda2 = false;
        players.at(1)->setVx(-200);
    }
    if(ev->key()==Qt::Key_6)
    {
         flag32 = false;
        players.at(1)->setVx(200);
        izquierda2 = true;
    }
    if(ev->key()==Qt::Key_8)
    {
       if(players.at(1)->getPy()==700-players.at(1)->getCheigh()){
           players.at(1)->setVy(-260);
       }

       for(int i =0;i<cosas.length();++i)
       {
           if(players.at(1)->collidesWithItem(cosas.at(i)))
           {
              flag2 = true;

              players.at(1)->setVy(-260);
              break;
           }
       }
       for(int i =obstaculos.length()-1;i>=0;i--)
       {
           if(players.at(1)->collidesWithItem(obstaculos.at(i)))
           {
               if(q2<4.0)
               {
                   flag32 = false;
                   players.at(1)->setVy(260);
               }
               else
               {
                   flag32 = true;
                   players.at(1)->setVy(-260);
               }
           }
       }
    }
    if(ev->key()==Qt::Key_2)
    {
        flag2 = true;
        players.at(1)->setVy(180);
    }
    //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB""
}

void batle::keyReleaseEvent(QKeyEvent *ev)
{


    if(ev->key()==Qt::Key_A)
    {
      players.at(0)->setVx(0);
    }
    if(ev->key()==Qt::Key_D)
    {
      players.at(0)->setVx(0);
    }
    if(ev->key()==Qt::Key_W)
    {
        flag3 = false;
        flag = false;
    }
    if(ev->key()==Qt::Key_S)
    {
        flag = false;
    }
    //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB""
    //teclas jugador 2**********************************************""
    if(ev->key()==Qt::Key_4)
    {
        players.at(1)->setVx(0);

    }
    if(ev->key()==Qt::Key_6)
    {

        players.at(1)->setVx(0);

    }
    if(ev->key()==Qt::Key_8)
    {
        flag32 = false;
        flag2 = false;
    }
    if(ev->key()==Qt::Key_2)
    {
        flag2 = false;
    }
    //BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB""

}

void batle::mousePressEvent(QMouseEvent *ev)
{
    mpos  = ev->pos();
}

void batle::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
           QPoint diff = ev->pos() - mpos;
           QPoint newpos = this->pos() + diff;
           this->move(newpos);
    }
}
