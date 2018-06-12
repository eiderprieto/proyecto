#ifndef USUARIO_H
#define USUARIO_H

#include <QWidget>
#include <QMessageBox>
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>
#include <QSize>
#include <QMovie>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>//consultas y requerimientos a la base de datos
#include <QtSql/QSqlError>//permite identificar los errores



#include "menu.h"
#include "opciones.h"
#include "niveles.h"

namespace Ui {
class usuario;
}

class usuario : public QWidget
{
    Q_OBJECT

public:
    explicit usuario(QWidget *parent = 0);
    ~usuario();

    int obtenerNivel();
    int getNivel() const;
    void setNivel(int value);

    int obtenerPuntaje();

private slots:
    void on_login_clicked();

    void on_salir_clicked();

    void on_create_clicked();

private:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    void creartablausuarios();
    void insertarUsuario();
    void obtenerusuarios();
    void ordenarTabla();

    int nivel;

    Ui::usuario *ui;
    QSqlDatabase db;
    QPoint mpos;
    bool flag =0;
    QMessageBox mensaje,mensaje1;

signals:

};

#endif // USUARIO_H
