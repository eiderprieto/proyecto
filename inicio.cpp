#include "inicio.h"
#include "ui_inicio.h"

inicio::inicio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicio)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente


    QPixmap imagen(":/imagenes/FIMAGENES.png");
    ui->loading->setPixmap(imagen);





    QMovie *movie = new QMovie(":/imagenes/LOADING-BLANCO.gif");
    QSize size(151, 141);
    movie->setScaledSize(size);
    ui->gif->setMovie(movie);
    movie->start();


}

inicio::~inicio()
{
    delete ui;
}

void inicio::mousePressEvent(QMouseEvent *ev)
{
    mpos=ev->pos();
}

void inicio::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
           QPoint diff = ev->pos() - mpos;
           QPoint newpos = this->pos() + diff;
           this->move(newpos);
    }
}

void inicio::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_F2)
    {
        delete this;
    }
}
