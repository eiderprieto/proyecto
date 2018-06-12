#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include <QWidget>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPoint>

#include "opciones.h"

namespace Ui {
class instrucciones;
}

class instrucciones : public QWidget
{
    Q_OBJECT

public:
    explicit instrucciones(QWidget *parent = 0);
    ~instrucciones();

private slots:
    void on_volver_clicked();

private:
    Ui::instrucciones *ui;

    QPoint mpos;

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
};

#endif // INSTRUCCIONES_H
