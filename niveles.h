#ifndef NIVELES_H
#define NIVELES_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <math.h>
#include <iostream>
#include "player.h"
#include "objetos.h"


using namespace std ;


namespace Ui {
class niveles;
}

class niveles : public QWidget
{
    Q_OBJECT

public:
    explicit niveles(QWidget *parent = 0);
    ~niveles();
    void objetosN1();
    void objetosN2();
    void objetosN3();
    void objetosN4();
    void objetosN5();
    void objetosN6();
    void objetosN7();
    void objetosN8();
    void objetosN9();



    bool getFlag() const;
    void setFlag(bool value);

    bool getFlag3() const;
    void setFlag3(bool value);

public slots:
    void actualizacion();
    void upScene();
    float CalCantidadD();
    float CalCantidadA();
    bool Sumaux();
    void moVbalas();


private:
    bool flagDir = 1,flagDirAnt = 1;
    Ui::niveles *ui;
    QGraphicsScene *scene;
    player *jugador;
    QList<objetos*>cosas;
    QList<objetos*>obstaculos;
    QList<objetos*>balas;


    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    QTimer *timer,*Tscene,*Taux,*Td,*Ta,*Tbalas;

    bool flag = true;// permite saltar al objeto cuando colisiona con cosas
    bool m; //determinar direcciones del jugador
    bool flag3 = true;// permite saltar al objeto cuando colisiona con obstaculos
    bool banCoy; //Bandera colisiones obstaculos en y
    bool banCcy;
    bool vderecha = true;

    float h,k;
    float x,y;
    float cont =0;
    float q2;







};

#endif // NIVELES_H
