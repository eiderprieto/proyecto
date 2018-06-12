#include "instrucciones.h"
#include "ui_instrucciones.h"

instrucciones::instrucciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instrucciones)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
}

instrucciones::~instrucciones()
{
    delete ui;
}

void instrucciones::on_volver_clicked()
{
    opciones *ops = new opciones();
    ops->show();
    delete this;
}

void instrucciones::mousePressEvent(QMouseEvent *ev)
{
    mpos = ev->pos();
}

void instrucciones::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        QPoint diff = ev->pos() - mpos;
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
}
