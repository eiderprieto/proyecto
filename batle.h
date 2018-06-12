#ifndef BATLE_H
#define BATLE_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <QMessageBox>

#include "opciones.h"
#include "objetos.h"
#include "player.h"

#define filasb 14    // variables que determinan el tamañana del arreglo que llenara el escenario de objetos
#define columnasb 26 // variables que determinan el tamañana del arreglo que llenara el escenario de objetos

namespace Ui {
class batle;
}

class batle : public QWidget
{
    Q_OBJECT

public:
    explicit batle(QWidget *parent = 0);
    void additems();
    ~batle();
    int cont =0;

public slots:
    void movebalas1(); // slot que mueve las balas del primer jugador
    void movebalas2(); // slot que mueve las balas del segundo jugador
    void actualizacion(); // slot que mueve las posiciones de los jugadores


private:

    bool izquierda1 ,izquierda2; // booleanos que sirven para determinar la direccion del disparo
    bool disbala1;  // boleano que permite disparar la primera bala luego de que el vector se vacie y no genere errores
    bool disbala2;  // boleano que permite disparar la primera bala luego de que el vector se vacie y no genere errores
    bool flag3;   // bandera que permite detectar la colision con los objetos del primer jugador(obstaculos)
    bool flag ;    // bandera que permite detectar la colision con los objetos del primer jugador(cosas)
    bool flag32;    // bandera que permite detectar la colision con los objetos del segundo jugador(obstaculos)
    bool flag2;     // bandera que permite detectar la colision con los objetos del segundo jugador(cosas)
    bool banCoy;         //Bandera colisiones obstaculos en y de los obstaculos del primer jugador ( si no esta colisionando se activa la gravedad)
    bool banCcy;         //Badera colisiones obstaculos en y de las cosas del primer jugador( si no esta colisionando se activa la gravedad)
    bool banCoy2;        //Bandera colisiones obstaculos en y de los obstaculos del segundo jugador ( si no esta colisionando se activa la gravedad)
    bool banCcy2;        //Bandera colisiones obstaculos en y de las cosas del segundo jugador ( si no esta colisionando se activa la gravedad)
    int reinicio;//reinicia el timer del nivel al perder

    float q2,q22;       // flotantes que permiten calcular la distancia entre el jugador y los objetos en cuestion
    float h,h2;         // flotantes que permiten calcular la distancia entre el jugador y los objetos en cuestion


    Ui::batle *ui;     //espacio donde se muestra la escena
    QGraphicsScene *scene; //escenario donde se mostrara el movimiento de los objetos

    //funcines y posiciones para detectar el movimiento del mouse y capturar un evento( arrastrar ventana)
    /**/ QPoint mpos;
    /**/void mousePressEvent(QMouseEvent *ev);
    /**/void mouseMoveEvent(QMouseEvent *ev);
    //fin del bloque para el arrastre de la ventana


    //funciones para capturar eventos de teclas ( presionada alguna tecla o no)
    /**/void keyPressEvent(QKeyEvent *ev);
    /**/void keyReleaseEvent(QKeyEvent *ev);
    //fin del bloque para capturar eventos de teclas


    QList<player*> players;     // lista de jugadores que se mostraran en pantalla
    QList<objetos*> obstaculos; // lista de objetos con los cuales los jugadores onteracturan en el escenario
    QList<objetos*> cosas;      // lista de objetos con caracteristicas especiales el cual el jugador usara para moverse dentro del mapa
    QList<objetos*> balas1;     //lista de objetos tipo "bala" que le perteneceran al jugador 1
    QList<objetos*> balas2;     //lista de objetos tipo "bala" que le perteneceran al jugador 2
    QList<objetos*> vidas1;     // lista de objetos visuales, que le perteneceran al jugador 1
    QList<objetos*> vidas2;     // lista de objetos visuales, que le perteneceran al jugador 1
    QMessageBox *gameover;      // mensaje que se desprende luego de que algun jugador tengas sus vidas en cero (0)


    char nivel[filasb][columnasb];// arreglo que sirve para llenar de objetos el escenario

    QTimer *Tbalas1,*Tbalas2,*Pjugador;




};

#endif // BATLE_H
