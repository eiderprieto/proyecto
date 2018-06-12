#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QGraphicsItem>
#include <QPoint>
#include <QMouseEvent>
#include <QProcess>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>//consultas y requerimientos a la base de datos
#include <QtSql/QSqlError>//permite identificar los errores


#include "niveles.h"
#include "usuario.h"
#include "opciones.h"

//comentario

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = 0);
    ~menu();

    QString getNombres() const;
    void setNombres(const QString &value);
    int nivel;
    int puntaje;

    int getNivel() const;
    void setNivel(int value);
    void bloqueo2();
    void bloqueo3();
    void bloqueo4();
    void bloqueo5();
    void bloqueo6();
    void bloqueo7();
    void bloqueo8();
    void bloqueo9();
    void borrarempezar();
    int obtenerPuntaje();


    int getPuntaje() const;
    void setPuntaje(int value);

private slots:
    void on_nivel1_clicked();

    void on_nivel2_clicked();

    void on_nivel3_clicked();

    void on_nivel4_clicked();

    void on_nivel5_clicked();

    void on_nivel6_clicked();

    void on_nivel7_clicked();

    void on_nivel8_clicked();

    void on_nivel9_clicked();

    void on_atras_clicked();

    void on_back_clicked();

    void on_cerrar_clicked();

    void on_cargar_clicked();

private:
    Ui::menu *ui;
    QString nombres;
    QSqlDatabase db;



    QPoint mpos;
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

};

#endif // MENU_H
