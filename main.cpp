#include "menu.h"
#include <QApplication>
#include "usuario.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    usuario w;
   // w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
   // w.setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
    w.show();

    return a.exec();
}
