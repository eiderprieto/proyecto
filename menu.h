#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QGraphicsItem>
#include "niveles.h"
#include "usuario.h"

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

private:
    Ui::menu *ui;

};

#endif // MENU_H
