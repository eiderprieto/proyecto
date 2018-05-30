#ifndef USUARIO_H
#define USUARIO_H

#include <QWidget>
#include <QString>
#include <QMessageBox>


#include "menu.h"

namespace Ui {
class usuario;
}

class usuario : public QWidget
{
    Q_OBJECT


    //usuario eider
    QString nombre="eiderprieto";
    QString contra="locarios1";

    //usuario julian
    QString Njulian="julian";
    QString ContraJulian="mauricio";


    QString nombre1,contra1;

public:
    explicit usuario(QWidget *parent = 0);
    ~usuario();

private slots:
    void on_login_clicked();

private:
    Ui::usuario *ui;
    menu *ventana;
    QMessageBox mensaje;
};

#endif // USUARIO_H
