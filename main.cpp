#include "menu.h"
#include <QApplication>
#include "usuario.h"
#include "inicio.h"
#include <QTimer>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
//    w.setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
    inicio *show=new inicio();
    show->show();
    usuario w;
    QTimer::singleShot(3400,show,SLOT(close()));
    QTimer::singleShot(3400,&w,SLOT(show()));


    return a.exec();
}
