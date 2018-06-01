#include "usuario.h"
#include "ui_usuario.h"

usuario::usuario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usuario)
{
    ui->setupUi(this);
    mensaje.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QString nombre;
    nombre.append("baseDedatos.sqlite");//nombre de la baso de datos

    db = QSqlDatabase::addDatabase("QSQLITE");//se le da el tipo de compilacion que se va a usar
    db.setDatabaseName(nombre);//funcion que le asigna un nombre a la base de datos

    if(db.open()) // crea la base de datos en el debugger, si la base de datos existe solo se conecta
    {
        qDebug()<<"conecto";
    }
    else
    {
        qDebug()<<"no conecto";
    }

    creartablausuarios();




   QFile user(":/documentos/user.txt"),pass(":/documentos/pass.txt");

   user.open(QIODevice::ReadWrite);
   pass.open(QIODevice::ReadWrite);



}

void usuario::creartablausuarios()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "nombre VARCHAR(100),"
                    "contraseña VARCHAR(100)"
                    ");");
    QSqlQuery crear;
    crear.prepare(consulta);

    if(crear.exec())
    {
        qDebug()<<"se creo correctamente";
    }
    else
    {
        qDebug()<<"no se creo";
        qDebug()<<"ERROR !"<<crear.lastError();
    }
}

void usuario::insertarUsuario()
{
    if(ui->password->text()==ui->password2->text())
    {
        QString consulta;
        consulta.append("INSERT INTO usuarios("
                        "nombre,"
                        "contraseña)"
                        "VALUES("
                        "'"+ui->nickname->text()+"',"
                        "'"+ui->password->text()+"'"
                        ");");
        QSqlQuery insertar;
        insertar.prepare(consulta);

        if(insertar.exec())
        {
            qDebug()<<"se inserto";
        }
        else
        {
            qDebug()<<"no se inserto";
            qDebug()<<"ERROR !"<<insertar.lastError();
        }
        mensaje.setText("El usuario fue creado, digite su nombre y su contraseña para iniciar");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.exec();
    }
    else
    {
        mensaje.setText("Las contraseñas no coinciden, intente de nuevo");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.exec();
    }

    ui->nickname->clear();
    ui->password->clear();
    ui->password2->clear();

}

void usuario::obtenerusuarios()
{
    QString consulta;
    consulta.append("SELECT * FROM usuarios");

    QSqlQuery consultar;
    consultar.prepare(consulta);

    if(consultar.exec())
    {
        qDebug()<<"se consulto";
    }
    else
    {
        qDebug()<<"no se consulto";
        qDebug()<<"ERROR !"<<consultar.lastError();
    }

}

void usuario::on_create_clicked()
{
    insertarUsuario();

}
usuario::~usuario()
{
    delete ui;
}

void usuario::on_login_clicked()
{
    flag = false; 
    obtenerusuarios();
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


void usuario::read(QFile text)
{
    if(!text.open(QFile::ReadOnly|QFile::Text))
    {
        mensaje.setText("Coul no open the resurces please try again");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.exec();
        return;
    }

    QTextStream in(&text);
    QString info = in.readAll();
    text.close();

}

void usuario::write(QFile text, QString write)
{
    if(!text.open(QFile::WriteOnly|QFile::Text))
    {
        mensaje.setText("Coul no open the resurces please try again");
        mensaje.setStandardButtons(QMessageBox::Close);
        mensaje.setDefaultButton(QMessageBox::Close);
        mensaje.exec();
        return;
    }

    QTextStream out(&text);
    out <<","+write;
    text.flush();

    text.close();
}
