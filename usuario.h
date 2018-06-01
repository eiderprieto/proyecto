#ifndef USUARIO_H
#define USUARIO_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>//consultas y requerimientos a la base de datos
#include <QtSql/QSqlError>//permite identificar los errores



#include "menu.h"
#include "opciones.h"

namespace Ui {
class usuario;
}

class usuario : public QWidget
{
    Q_OBJECT


    QString nombre,contra,contra1;

    QVector<QString> usuarios={"eider","julian"};
    QVector<QString> contrasenas={"locarios","mauricio"};

public:
    explicit usuario(QWidget *parent = 0);

    void creartablausuarios();
    void insertarUsuario();
    void obtenerusuarios();
    ~usuario();

private slots:
    void on_login_clicked();

    void on_salir_clicked();

    void on_create_clicked();

private:
    Ui::usuario *ui;

    QSqlDatabase db;
    bool flag =0;

    void read(QFile text);
    void write(QFile text, QString write);


    QMessageBox mensaje,mensaje1;

};

#endif // USUARIO_H
