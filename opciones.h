#ifndef OPCIONES_H
#define OPCIONES_H

#include <QWidget>
#include "menu.h"

namespace Ui {
class opciones;
}

class opciones : public QWidget
{
    Q_OBJECT

public:
    explicit opciones(QWidget *parent = 0);
    ~opciones();

private slots:
    void on_arcade_clicked();

private:
    Ui::opciones *ui;
};

#endif // OPCIONES_H
