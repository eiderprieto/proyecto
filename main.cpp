#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    menu w;
//    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
//    w.setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente

    w.show();
    return a.exec();
}
