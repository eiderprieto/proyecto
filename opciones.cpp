#include "opciones.h"
#include "ui_opciones.h"

opciones::opciones(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opciones)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente


    QPixmap pic(":/imagenes/nuclear1.jpg");
    QPixmap picScaled(pic.scaled(600, 400, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->imagen->setPixmap(picScaled);

}

opciones::~opciones()
{
    delete ui;
}

int opciones::getNivel() const
{
    return nivel;
}

void opciones::setNivel(int value)
{
    nivel = value;
}

QString opciones::getNombres() const
{
    return nombres;
}

void opciones::setNombres(const QString &value)
{
    nombres = value;

}

void opciones::on_arcade_clicked()//se obtiene una respuesta de boton sobre que divel tener bloqueados
{
    menu *volver = new menu();
    volver->setNombres(nombres);
    volver->setPuntaje(puntaje);
    volver->setNivel(nivel);
    if(volver->getNivel()==2)volver->bloqueo2();
    if(volver->getNivel()==3)volver->bloqueo3();
    if(volver->getNivel()==4)volver->bloqueo4();
    if(volver->getNivel()==5)volver->bloqueo5();
    if(volver->getNivel()==6)volver->bloqueo6();
    if(volver->getNivel()==7)volver->bloqueo7();
    if(volver->getNivel()==8)volver->bloqueo8();
    if(volver->getNivel()==9)volver->bloqueo9();
    volver->show();
    delete this;
}

void opciones::on_battle_clicked()
{
    batle *batalla = new batle();
    batalla->additems();
    batalla->show();
    delete this;
}
void opciones::mousePressEvent(QMouseEvent *ev)
{
    mpos = ev->pos();
}
void opciones::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        QPoint diff = ev->pos() - mpos;
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
}

void opciones::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_F1)
    {
        usuario *volver = new usuario();
        volver->show();
        delete this;
    }
    if(ev->key()==Qt::Key_F2)
    {
        delete this;
    }
}
void opciones::on_back_clicked()
{
    usuario *volver = new usuario();
    volver->show();
    delete this;
}

void opciones::on_instruccions_clicked()
{
    instrucciones *instru = new instrucciones();
    instru->show();
    delete this;
}

int opciones::getPuntaje() const
{
    return puntaje;
}

void opciones::setPuntaje(int value)
{
    puntaje = value;
}

