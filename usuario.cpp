#include "usuario.h"
#include "ui_usuario.h"

usuario::usuario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usuario)
{
    ui->setupUi(this);
}

usuario::~usuario()
{
    delete ui;
}

void usuario::on_login_clicked()
{
    nombre1 = ui->Nombreusuario->text();
    contra1 = ui->contra->text();

    if((nombre1 == nombre)&&(contra1 == contra))
    {
        menu *ventana = new menu();
        //ventana->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
        //ventana->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
        ventana->show();
        this->close();
    }

    else if((nombre1 == Njulian)&&(contra1==ContraJulian))
    {
            menu *ventana = new menu();
          //  ventana->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
          //  ventana->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
            ventana->show();
            this->close();
    }

    else if(nombre1!=nombre && nombre1!=Njulian)
    {
        mensaje.setText("Usuario no registrado");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.show();
    }
    else if(contra1!=contra && contra1!=ContraJulian)
    {
        mensaje.setText("Contraseña incorrecta");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.show();
    }

    else if(nombre1==nombre && contra1==ContraJulian)
    {
        mensaje.setText("Contraseña incorrecta");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.show();
    }
    else if(nombre1==Njulian && contra1==contra)
    {
        mensaje.setText("Contraseña incorrecta");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.show();
    }


}

void usuario::on_salir_clicked()
{
    this->close();
}
