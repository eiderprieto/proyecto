#include "opciones.h"
#include "ui_opciones.h"

opciones::opciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opciones)
{
    ui->setupUi(this);
}

opciones::~opciones()
{
    delete ui;
}

void opciones::on_arcade_clicked()
{
    menu *ventana = new menu();
    //ventana->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    //ventana->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
    ventana->show();
    this->close();
}
