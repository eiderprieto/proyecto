#include "usuario.h"
#include "ui_usuario.h"
#include "usuario.h"

usuario::usuario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usuario)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente

    QMovie *movie = new QMovie(":/imagenes/ingreso1.gif");
    QSize size(600, 400);
    movie->setScaledSize(size);
    ui->imagen->setMovie(movie);
    movie->start();

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


}

void usuario::creartablausuarios()
{
    QString consulta;
    consulta.append("CREATE TABLE IF NOT EXISTS usuarios("//crea una tabla
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
    QString verificar;//string que se le asigna a la consulta para verificar si el usuario existe
    QSqlQuery inserto;// consulta para verificar que no se coloque el mismo usuario en la base de datos
    QString consulta; //string de consulta para insertar el usuario a la base de datos
    QSqlQuery insertar;// consulta que inserta en la base de datos el usuario y la contraseña creadas

    verificar.append("SELECT * FROM usuarios WHERE nombre='"+ui->nickname->text()+"'");
    inserto.prepare(verificar);
    if(!(ui->nickname->text()=="")&&((!(ui->password->text()==""))||!(ui->password2->text()=="")))
    {
        if(inserto.exec())
        {
            if(!(inserto.at()==-1))//si existe un usuario arroja -1
            {
                if(ui->password->text()==ui->password2->text())
                {
                    consulta.append("INSERT INTO usuarios("
                                    "nombre,"
                                    "contraseña)"
                                    "VALUES("
                                    "'"+ui->nickname->text()+"',"
                                    "'"+ui->password->text()+"'"
                                    ");");
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

            }
            else
            {
                mensaje.setText("El nombre de usuario esta en uso intente con otro");
                mensaje.setStandardButtons(QMessageBox::Close);
                mensaje.setDefaultButton(QMessageBox::Close);
                mensaje.exec();
            }
        }
        else
        {
            qDebug()<<"no miro;";
            mensaje.setText("Unknow mistake please Contact + 57 3024283839");
            mensaje.setStandardButtons(QMessageBox::Close);
            mensaje.setDefaultButton(QMessageBox::Close);
            mensaje.exec();
        }
    }
    else
    {
        mensaje.setText("No se pueden campos vacios");
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
    consulta.append("SELECT * FROM usuarios WHERE nombre='"+ui->Nombreusuario->text()+
                    "' AND contraseña='"+ui->contra->text()+"'");

    QSqlQuery consultar;
    consultar.prepare(consulta);

    if(consultar.exec())
    {
        qDebug()<<"se consulto";
        if(consultar.at()==-1)
        {
            opciones *siguiente = new opciones();
            siguiente->show();
            siguiente->setNivel(obtenerNivel());
            siguiente->setPuntaje(obtenerPuntaje());
            siguiente->setNombres(ui->Nombreusuario->text());
            this->close();
        }
        else
        {
            mensaje.setText("Nombre de usuario y/o contraseña incorrectos");
            mensaje.setStandardButtons(QMessageBox::Close);
            mensaje.setDefaultButton(QMessageBox::Close);
            mensaje.exec();
        }
    }
    else
    {
        qDebug()<<"no se consulto";
        qDebug()<<"ERROR !"<<consultar.lastError();
    }

}

void usuario::ordenarTabla()
{
    QString consulta;
    consulta.append("SELECT * FROM datosUsuarios ORDER BY nivel ASC;");
        QSqlQuery consultar;
        consultar.prepare(consulta);

        if(consultar.exec())

        {
           qDebug()<<" se ordeno";

        }
        else
        {
            qDebug()<<"no se ordeno";
            qDebug()<<"ERROR !"<<consultar.lastError();
        }
}

int usuario::getNivel() const
{
    return nivel;
}

void usuario::setNivel(int value)
{
    nivel = value;
}

int  usuario::obtenerPuntaje()
{
        QString consulta;
        consulta.append("SELECT puntaje FROM datosUsuarios WHERE nombre='"+ui->Nombreusuario->text()+"';");
        QSqlQuery consultar;
        consultar.prepare(consulta);

        if(consultar.exec())
        {
            consultar.next();
            qDebug()<<"retornó puntaje";
            return consultar.value(0).toInt();
        }
        else
        {
            qDebug()<<"no retornó el puntaje";
            qDebug()<<"ERROR !"<<consultar.lastError();
            return NULL;
        }
}
int usuario::obtenerNivel()
{

    QString consulta;
    consulta.append("SELECT nivel FROM datosUsuarios WHERE nombre='"+ui->Nombreusuario->text()+"';");
        QSqlQuery consultar;
        consultar.prepare(consulta);

        if(consultar.exec())
        {
            consultar.next();

            return consultar.value(0).toInt();
        }
        else
        {
            qDebug()<<"no se consulto";
            qDebug()<<"ERROR !"<<consultar.lastError();
            return NULL;
        }
}


void usuario::on_create_clicked()
{
    insertarUsuario();
}

void usuario::mousePressEvent(QMouseEvent *ev)
{
    mpos = ev->pos();
}

void usuario::mouseMoveEvent(QMouseEvent *ev)
{
        if (ev->buttons() & Qt::LeftButton)
        {
               QPoint diff = ev->pos() - mpos;
               QPoint newpos = this->pos() + diff;
               this->move(newpos);
        }
}
usuario::~usuario()
{
    delete ui;
}

void usuario::on_login_clicked()
{
    obtenerusuarios();
    ordenarTabla();

}

void usuario::on_salir_clicked()
{
    this->close();
}

