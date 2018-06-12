#ifndef NIVELES_H
#define NIVELES_H

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
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <QFile>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QBitArray>
#include <QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>//consultas y requerimientos a la base de datos
#include <QtSql/QSqlError>//permite identificar los errores


#include "player.h"
#include "objetos.h"
#include "menu.h"
#include "niveles.h"


#define filas 31
#define columnas 36


using namespace std ;

namespace Ui {
class niveles;
}
class QSerialPort;


class niveles : public QWidget
{
    Q_OBJECT

public:
    explicit niveles(QWidget *parent = 0);
    ~niveles();
    void objetosN1(); //funcion que llama los objetos del nivel 1
    void objetosN2(); //funcion que llama los objetos del nivel 2
    void objetosN3(); //funcion que llama los objetos del nivel 3
    void objetosN4(); //funcion que llama los objetos del nivel 4
    void objetosN5(); //funcion que llama los objetos del nivel 5
    void objetosN6(); //funcion que llama los objetos del nivel 6
    void objetosN7(); //funcion que llama los objetos del nivel 7
    void objetosN8(); //funcion que llama los objetos del nivel 8
    void objetosN9(); //funcion que llama los objetos del nivel 9
    bool serialInit(void);
    int obtenerNivel();


    QString getNombres() const;
    void setNombres(const QString &value);

public slots:
    void actualizacion(); // slot que permitira la actualizacion de las posiciones de cada objeto en el mapa
    void upScene();       // slot que realiza el movimiento de la escena
    float CalCantidadD(); // slot que captura el desfase de la escena correspondiente al jugador hacia la izquierda
    float CalCantidadA(); // slot que captura el desfase de la escena correspondiente al jugador hacia la derecha
    bool Sumaux();        //slot que retorna un boleano en tiempo de ejecucion par determinar la direccion del jugador ( izquierda, derecha)
    void moVbalas();      // slot de objetos correspondiente al movimiento de las bajas del personaje principal
    void verificacion();



private:
    bool flagDir = 1,flagDirAnt = 1; // banderas que permiten detectar el cambio de direccion
    QString nombres;
    Ui::niveles *ui;           // escenario donde se cargaran todas las escenas
    QGraphicsScene *scene;     // escenario donde se cargran los objetos e interactuarán
    player *jugador;           // objeto jugador principal
    QList<objetos*>cosas;      // lista de cosas que se pueden atravesar (plataformas)
    QList<objetos*>obstaculos; // lista de obstaculos que no se pueden atravesar (ladrillos,paredes)
    QList<objetos*>balas;      // lista de balas disparadas por el jugador
    QList<objetos*> vidas;     // vidas del jugador
    QList<objetos*>puertas;    // objeto que permite al jugador pasar de nivel
    QList<objetos*> enemigos;  // lista de enemigos presentes en el nivel
    QList<objetos*> auxiliar;  // lista auxiliar que sirve para lleñar una matriz correspondiente a las vidas de los enemigos presentes en el mapa
    QList<objetos*> salud;
    QList<objetos*> monedas;
    QList<QList<objetos*>> VidasEnemigos; // lista que se llena con la lista auxiliar anterior

    QMessageBox *mensaje;      // mensaje emergente correspondiente a noticias luego de un evento
    QSqlDatabase db;
    QMessageBox *gameover;
    int vidasJugador =1;
    int nivelJugador;
    int cantEnemigos=1;
    int score=1;

    char nivel1[filas][columnas]; // arreglo que se llena con los objetos a añadir al mapa
    char nivel[filas][columnas];

    // punto que detectará la posicion del mouse conforme al graphicsview
    /**/QPoint mpos;
    /**/void mousePressEvent(QMouseEvent *ev);
    /**/void mouseMoveEvent(QMouseEvent *ev);
    //fin de la deteccion del mouse

    void creartablacaracteristicas();
    void obtenerusuarios();
    void insertarvalores();

    void actualizarvalores();
    int obtenerPuntaje();

    void keyPressEvent(QKeyEvent *ev);
    void keyReleaseEvent(QKeyEvent *ev);
    QTimer *timer,*Tscene,*Taux,*Td,*Ta,*Tbalas,*Tproyectil,*Tveri;

    bool flag = true;// permite saltar al objeto cuando colisiona con cosas
    bool m; //determinar direcciones del jugador
    bool flag3 = true;// permite saltar al objeto cuando colisiona con obstaculos
    bool banCoy; //Bandera colisiones obstaculos en y
    bool banCcy;
    bool vderecha = true;
    bool disbala= true;
    bool reinicio=false;//reinicia el timer del nivel al perder


    float h,k;    // flotantes que determinan la distancia entre el jugador y los objetos
    float x,y;    //
    float xv,yv;  // posicion del jugador
    float cont =0;//up scene
    float q2;
    float balitas=0;
    int rand=0;
    float vidas1; // flotante que determina las vidas de los enemigos en cada nivel
    float xE,yE;  //posicion de los enemigos
    float posV;   //mitad de la posicion de las balas

    int puntaje;

    //Empieza el arduino mijaaaa
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;//
    static const quint16 arduino_uno_product_id = 67;//**************ni idea***************
    QString arduino_port_name;//nombre del arduino disponible
    bool arduino_is_available;// mira si  hay arduino disponible
    QSerialPort serial;

    //Fin del arduino



};

#endif // NIVELES_H
