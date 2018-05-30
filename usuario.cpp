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
    flag = false;
    nombre = ui->Nombreusuario->text();
    contra = ui->contra->text();
    for(int i =0;i<usuarios.length();i++)
    {
        if(usuarios.at(i)==nombre)
        {
            flag = true;
            if(contrasenas.at(i)==contra)
            {
                opciones *ops = new opciones();
                //ventana->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
                //ventana->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente
                ops->show();
                this->close();
            }
            else
            {
                mensaje.setText("Contrasena incorrecta");
                mensaje.setStandardButtons(QMessageBox::Close);
                mensaje.setDefaultButton(QMessageBox::Close);
                mensaje.exec();
            }
        }
    }
    if(!flag)
    {
        mensaje.setText("Usuario No registrado");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.exec();
    }


}

void usuario::on_salir_clicked()
{
    this->close();
}

void usuario::on_create_clicked()
{
    nombre = ui->nickname->text();
    contra = ui->password->text();
    contra1= ui->password2->text();




    ui->nickname->clear();
    ui->password->clear();
    ui->password2->clear();

}
