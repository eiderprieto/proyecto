#ifndef USUARIO_H
#define USUARIO_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QFile>


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
    ~usuario();

private slots:
    void on_login_clicked();

    void on_salir_clicked();

    void on_create_clicked();

private:
    Ui::usuario *ui;
    bool flag =0;


    QMessageBox mensaje,mensaje1;
};

#endif // USUARIO_H
