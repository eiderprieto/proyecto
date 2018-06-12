#ifndef OPCIONES_H
#define OPCIONES_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QKeyEvent>
#include <QPixmap>


#include "menu.h"
#include "batle.h"
#include "usuario.h"
#include "instrucciones.h"


namespace Ui {
class opciones;
}

class opciones : public QWidget
{
    Q_OBJECT
    QString nombres;

public:
    explicit opciones(QWidget *parent = 0);
    ~opciones();
    int nivel;



    QString getNombres() const;
    void setNombres(const QString &value);

    int getNivel() const;
    void setNivel(int value);

    int getPuntaje() const;
    void setPuntaje(int value);

private slots:
    void on_arcade_clicked();

    void on_battle_clicked();

    void on_back_clicked();

    void on_instruccions_clicked();

public slots:


private:
    Ui::opciones *ui;
    QPoint mpos;
    int puntaje;


    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    void keyPressEvent(QKeyEvent *ev);


};

#endif // OPCIONES_H
