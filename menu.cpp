#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente

    QPixmap imagen(":/imagenes/menu.png");
    ui->imagen->setPixmap(imagen);


    ui->nivel2->setEnabled(false);
    ui->nivel3->setEnabled(false);
    ui->nivel4->setEnabled(false);
    ui->nivel5->setEnabled(false);
    ui->nivel6->setEnabled(false);
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);



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
}

menu::~menu()
{
    delete ui;
}

void menu::on_nivel1_clicked()//se carga al presionarse el boton
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN1();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel2_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN2();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel3_clicked()
{

    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN3();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel4_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN4();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel5_clicked()
{

    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN5();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel6_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN6();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel7_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN7();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel8_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN8();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_nivel9_clicked()
{
    niveles *escenarios = new niveles();
    escenarios->setNombres(nombres);
    escenarios->objetosN9();
    escenarios->actualizacion();
    escenarios->show();
    delete this;
}

void menu::on_atras_clicked()
{
    usuario *user = new usuario();
    user->show();
    delete this;
}

void menu::mousePressEvent(QMouseEvent *ev)
{
    mpos = ev->pos();
}

void menu::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
           QPoint diff = ev->pos() - mpos;
           QPoint newpos = this->pos() + diff;
           this->move(newpos);
    }
}

void menu::on_back_clicked()
{
    opciones *ventana = new opciones();
    ventana->setNombres(nombres);
    ventana->setNivel(nivel);
    ventana->show();
    delete this;
}

void menu::on_cerrar_clicked()
{
    delete this;
}

QString menu::getNombres() const
{
    return nombres;
}

void menu::setNombres(const QString &value)
{
    nombres = value;
}

int menu::getPuntaje() const
{
    return puntaje;
}

void menu::setPuntaje(int value)
{
    puntaje = value;
    //ui->valor->setStyleSheet("#label{color: #ff7700;}#label:hover{color:rgb(255, 255, 255);}");
    ui->valor->setText(QString::number(obtenerPuntaje()));
}

int menu::getNivel() const
{
    return nivel;
}

void menu::setNivel(int value)
{
    nivel = value;
}

void menu::bloqueo2()
{

    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(false);
    ui->nivel4->setEnabled(false);
    ui->nivel5->setEnabled(false);
    ui->nivel6->setEnabled(false);
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);

}

void menu::bloqueo3()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(false);
    ui->nivel5->setEnabled(false);
    ui->nivel6->setEnabled(false);
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo4()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(false);
    ui->nivel6->setEnabled(false);
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo5()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(true);
    ui->nivel5->setStyleSheet("#nivel5{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/5.png);}"
                              "#nivel5:hover{border:10px solid #5cfdff;}");
    ui->nivel6->setEnabled(false);
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo6()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(true);
    ui->nivel5->setStyleSheet("#nivel5{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/5.png);}"
                              "#nivel5:hover{border:10px solid #5cfdff;}");
    ui->nivel6->setEnabled(true);
    ui->nivel6->setStyleSheet("#nivel6{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/6.png);}"
                              "#nivel6:hover{border:10px solid #5cfdff;}");
    ui->nivel7->setEnabled(false);
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo7()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(true);
    ui->nivel5->setStyleSheet("#nivel5{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/5.png);}"
                              "#nivel5:hover{border:10px solid #5cfdff;}");
    ui->nivel6->setEnabled(true);
    ui->nivel6->setStyleSheet("#nivel6{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/6.png);}"
                              "#nivel6:hover{border:10px solid #5cfdff;}");
    ui->nivel7->setEnabled(true);
    ui->nivel7->setStyleSheet("#nivel7{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/7.png);}"
                              "#nivel7:hover{border:10px solid #5cfdff;}");
    ui->nivel8->setEnabled(false);
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo8()
{

    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(true);
    ui->nivel5->setStyleSheet("#nivel5{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/5.png);}"
                              "#nivel5:hover{border:10px solid #5cfdff;}");
    ui->nivel6->setEnabled(true);
    ui->nivel6->setStyleSheet("#nivel6{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/6.png);}"
                              "#nivel6:hover{border:10px solid #5cfdff;}");
    ui->nivel7->setEnabled(true);
    ui->nivel7->setStyleSheet("#nivel7{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/7.png);}"
                              "#nivel7:hover{border:10px solid #5cfdff;}");
    ui->nivel8->setEnabled(true);
    ui->nivel8->setStyleSheet("#nivel8{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/8.png);}"
                              "#nivel8:hover{border:10px solid #5cfdff;}");
    ui->nivel9->setEnabled(false);
}

void menu::bloqueo9()
{
    ui->nivel2->setEnabled(true);
    ui->nivel2->setStyleSheet("#nivel2{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/2.png);}"
                              "#nivel2:hover{border:10px solid #5cfdff;}");
    ui->nivel3->setEnabled(true);
    ui->nivel3->setStyleSheet("#nivel3{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/3.png);}"
                              "#nivel3:hover{border:10px solid #5cfdff;}");
    ui->nivel4->setEnabled(true);
    ui->nivel4->setStyleSheet("#nivel4{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/4.png);}"
                              "#nivel4:hover{border:10px solid #5cfdff;}");
    ui->nivel5->setEnabled(true);
    ui->nivel5->setStyleSheet("#nivel5{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/5.png);}"
                              "#nivel5:hover{border:10px solid #5cfdff;}");
    ui->nivel6->setEnabled(true);
    ui->nivel6->setStyleSheet("#nivel6{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/6.png);}"
                              "#nivel6:hover{border:10px solid #5cfdff;}");
    ui->nivel7->setEnabled(true);
    ui->nivel7->setStyleSheet("#nivel7{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/7.png);}"
                              "#nivel7:hover{border:10px solid #5cfdff;}");
    ui->nivel8->setEnabled(true);
    ui->nivel8->setStyleSheet("#nivel8{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/8.png);}"
                              "#nivel8:hover{border:10px solid #5cfdff;}");
    ui->nivel9->setEnabled(true);
    ui->nivel9->setStyleSheet("#nivel9{ border:5px solid #42aaf4; border-radius: 15px;"
                              "background-image: url(:/imagenes/niveles/9.png);}"
                              "#nivel9:hover{border:10px solid #5cfdff;}");
}

void menu::borrarempezar()
{
    QString consulta;
    consulta.append("DELETE FROM datosUsuarios WHERE nombre='"+nombres+"';");
    QSqlQuery consultar;
    consultar.prepare(consulta);

    if(consultar.exec())
    {
        consultar.next();
        qDebug()<<"SE BORRO";
        menu *nuevo = new menu();
        nuevo->setNombres(nombres);
        nuevo->show();
        delete this;
    }
    else
    {
        qDebug()<<"NO SE BORRO";
        qDebug()<<"ERROR !"<<consultar.lastError();
    }
}

int menu::obtenerPuntaje()
{
    QString consulta;
    consulta.append("SELECT puntaje FROM datosUsuarios WHERE nombre='"+nombres+"';");
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

void menu::on_cargar_clicked()
{
    borrarempezar();
}
