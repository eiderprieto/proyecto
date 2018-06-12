#include "niveles.h"
#include "ui_niveles.h"

niveles::niveles(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::niveles)
{
    ui->setupUi(this);


    QString nombreS;
    nombreS.append("baseDedatos.sqlite");//nombre de la baso de datos

    db = QSqlDatabase::addDatabase("QSQLITE");//se le da el tipo de compilacion que se va a usar
    db.setDatabaseName(nombreS);//funcion que le asigna un nombre a la base de datos

    if(db.open()) // crea la base de datos en el debugger, si la base de datos existe solo se conecta
    {
        qDebug()<<"conecto";
    }
    else
    {
        qDebug()<<"no conecto";
    }

    creartablacaracteristicas();
     //obtenerusuarios();

    //fin de la conexion en la base de datos


    serial.setPortName("COM4"); //Poner el nombre del puerto, probablemente no sea COM3

    if(serial.open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!serial.setBaudRate(QSerialPort::Baud115200)) //Configurar la tasa de baudios
            qDebug()<<serial.errorString();

        if(!serial.setDataBits(QSerialPort::Data8))
            qDebug()<<serial.errorString();

        if(!serial.setParity(QSerialPort::NoParity))
            qDebug()<<serial.errorString();

        if(!serial.setStopBits(QSerialPort::OneStop))
            qDebug()<<serial.errorString();

        if(!serial.setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<serial.errorString();
    }else{
        qDebug()<<"Serial COM4 not opened. Error: "<<serial.errorString();
    }


    //Arduino funcion
    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    //conexion con la base de datos

    //Pruebas.......
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();//
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()){
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }


    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if(arduino_is_available){
        // open and configure the serialport
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
    //fin arduino


    //creacion de la escena
    /**/scene = new QGraphicsScene();
    /**/scene->setSceneRect(0,0,1000,500);
    //fin de la creacion de la escena

    //fondo de la escena.........................................
    /**/  QPixmap brusher(":/imagenes/escenarios/fondo1.png");
    /**/  QGraphicsPixmapItem *item = scene->addPixmap(brusher);
    /**/  item->setPos(0,-1000);
    /**/  scene->addPixmap(brusher)->setPos(0,-1000);
    //fin del fondo de la escena.................................

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background: transparent");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);//quitar los bordes y botones
    this->setAttribute(Qt::WA_TranslucentBackground);//ponerla transparente



    timer      = new QTimer();
    Tscene     = new QTimer();
    Taux       = new QTimer();
    Td         = new QTimer();
    Ta         = new QTimer();
    Tbalas     = new QTimer();
    Tveri      = new QTimer();




    //bordes de la escena
    /**/obstaculos.append(new objetos(-400,-250,800,2000,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    /**/scene->addItem(obstaculos.last());//Izquierda
    /**/obstaculos.append(new objetos(2200,-250,800,2000,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    /**/scene->addItem(obstaculos.last());//Derecha
    /**/obstaculos.append(new objetos(900,-1150,1800,300,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    /**/scene->addItem(obstaculos.last());//Arriba
    /**/obstaculos.append(new objetos(900,650,1800,300,":/imagenes/escenarios/bordes.jpg",Qt::darkBlue));
    /**/scene->addItem(obstaculos.last());//Abajo
    //fin de bordes de la escena



    //conexion de los timers
    /**/connect(Tscene,SIGNAL(timeout()),this,SLOT(upScene()));
    /**/connect(timer,SIGNAL(timeout()),this,SLOT(actualizacion()));
    /**/connect(Taux,SIGNAL(timeout()),this,SLOT(Sumaux()));
    /**/connect(Td,SIGNAL(timeout()),this,SLOT(CalCantidadD()));
    /**/connect(Ta,SIGNAL(timeout()),this,SLOT(CalCantidadA()));
    /**/connect(Tbalas,SIGNAL(timeout()),this,SLOT(moVbalas()));
    /**/connect(Tveri,SIGNAL(timeout()),this,SLOT(verificacion()));
    //fin de la conexion de los timers


    //inicializacion de los timers
    /**/timer->start(2);
    /**/Tscene->start(10);
    /**/Taux->start(19);
    /**/Tbalas->start(6);
    /**/Tveri->start(200);
    //fin de la inicializacion de los timers

    vidas1=3;
    puntaje =0;
    nivelJugador = 1;

}

niveles::~niveles()
{
    delete ui;
}

void niveles::objetosN1()
{
    int i=filas;int j=0;
    posV = vidas1*10/2.0;
      nivelJugador = 1;

    QFile archivos(":/documentos/nivel1.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }

    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)//se cargan las vidas del jugados
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }
}

void niveles::objetosN2()
{
    vidas1++;
    int i=filas;int j=0;int num=0;
      nivelJugador = 2;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel2.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }

    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }
}

void niveles::objetosN3()
{
    vidas1+=2;
    int i=filas;int j=0;
    nivelJugador = 3;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel3.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }

    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }

}

void niveles::objetosN4()
{
    vidas1+=3;
    int i=filas;int j=0;

    nivelJugador = 4;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel4.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }


}

void niveles::objetosN5()
{
    int i=filas;int j=0;
    vidas1+=4;
    nivelJugador = 5;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel5.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }


}

void niveles::objetosN6()
{
    int i=filas;int j=0;
    vidas1+=5;
    posV = vidas1*10/2.0;
    nivelJugador = 6;
    QFile archivos(":/documentos/nivel6.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }
}

void niveles::objetosN7()
{
    int i=filas;int j=0;
    vidas1+=6;
    nivelJugador = 7;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel7.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }
}

void niveles::objetosN8()
{
    int i=filas;int j=0;
    vidas1+=7;
    nivelJugador = 8;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel8.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    ui->graphicsView->setFocus();
    for(int i=0;i<10;i++)
    {
        vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }

}

void niveles::objetosN9()
{
    int i=filas;int j=0;
    vidas1+=8;
    nivelJugador = 9;
    posV = vidas1*10/2.0;
    QFile archivos(":/documentos/nivel2.txt");
    int i1=filas;
    int j1 = 0;
    char file_data;
    if(archivos.open(QIODevice::ReadOnly))
    {
        qDebug()<<"file open"<<endl;
        while(!archivos.atEnd())
        {   archivos.read(&file_data,sizeof(char));
            if(!(file_data=='\t')&&!(file_data=='\n')&&!(int(file_data)==13))
            {
                nivel[i][j]=file_data;
                if(nivel[i][j]=='b')
                {
                    obstaculos.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillos.png",Qt::darkBlue));
                    scene->addItem(obstaculos.last());
                }
                if(nivel[i][j]=='c')
                {
                    cosas.append(new objetos((j1*50)+25,500-(i1*50)+25,50,50,":/imagenes/escenarios/ladrillo gris 1.png",Qt::gray));
                    scene->addItem(cosas.last());
                }

                if(nivel[i][j]=='p')
                {
                    puertas.append(new objetos((j1*50)+35,500-(i1*50)+50,70,100,":/imagenes/puerta/puerta.png",Qt::cyan));
                    scene->addItem(puertas.last());
                }
                if(nivel[i][j]=='e')
                {
                    enemigos.append(new objetos((j1*50)+25,500-(i1*50)+15,50,70,70,10*(1+qrand()%16),vidas1,":/imagenes/escenarios/cuadrado.jpg",Qt::cyan));
                    scene->addItem(enemigos.last());
                    for(int m=0;m<vidas1;m++)
                    {
                          auxiliar.append(new objetos(0,0,10,4,":/imagenes/ratas 2.0/vidas/vidaEnemigos.png",Qt::red));
                        scene->addItem(auxiliar.last());
                    }
                    VidasEnemigos.append(auxiliar);
                    auxiliar.clear();
                }
                if(nivel[i][j]=='h')
                {
                    salud.append(new objetos((j1*50)+24,500-(i1*50)+24,24,24));
                    scene->addItem(salud.last());
                }
                if(nivel[i][j]=='m')
                {
                    monedas.append(new objetos((j1*50)+25,500-(i1*50)+25,24,24,0));
                    scene->addItem(monedas.last());
                }

                if(j1==columnas-1)
                {
                    j1=0;
                    i1--;
                }
                else
                {
                    j1++;
                }
            }
        }
        archivos.close();
    }
    else
    {
        qDebug()<<"file not opened"<<endl;
        return ;
    }
    jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
    scene->addItem(jugador);
    for(int i=0;i<5;i++)
    {
        vidas.append(new objetos(0,0,20,4,":/imagenes/vidaJugador.png",Qt::green));
        scene->addItem(vidas.last());
    }
}

void niveles::actualizacion()
{
   //movimiento desde el serial del bluetooth
    char data;//caracter que recibe desde el bt
    int l = 0;//entero ue dice si recibio
    //l = serial.read(&data,1);
    if(l!=0){//si le entro señal

        if(data=='R')//rigth
        {
            Ta->stop();
            flagDir = 1;
            if(Sumaux())
            {
                if(cont>0)
                    cont =0;
                Td->start(2);
            }
            jugador->setVx(180);
        }
        if(data=='L')//left
        {
            flag3 = false;
            Td->stop();
            flagDir = 0;
            if(Sumaux())
            {
                if(cont<-399)
                    cont =0;
                Ta->start(2);
            }
            jugador->setVx(-180);
        }

        if(data=='T')//top
        {
            for(int i =obstaculos.length()-1;i>=0;i--)
            {
                if(jugador->collidesWithItem(obstaculos.at(i)))
                {
                    if(q2<4.0)
                    {
                        flag3 = false;
                        jugador->setVy(300);
                    }
                    else
                    {
                        flag3 = true;
                        jugador->setVy(-300);
                    }
                }
            }

            for(int i =0;i<cosas.length();++i)
                {
                    if(jugador->collidesWithItem(cosas.at(i)))
                    {
                        flag = true;

                        jugador->setVy(-300);
                        break;
                    }
                }
                if(jugador->getPy()==500-jugador->getCheigh()){
                    jugador->setVy(-300);
                }
            }

            if(data=='D')//donw
            {
                jugador->setVy(200);
                flag = true;

            }
            if(data=='S')//Shot
            {
                if(disbala)
                        {
                            balas.append(new objetos(jugador->getPx(),jugador->getPy(),40,12,300,":/imagenes/laser1.png",Qt::black,vderecha));
                            scene->addItem(balas.last());
                            disbala = false;
                        }
                        if(abs(balas.last()->getPx()-jugador->getPx())>150)
                        {
                            balas.append(new objetos(jugador->getPx(),jugador->getPy(),40,12,300,":/imagenes/laser1.png",Qt::black,vderecha));
                            scene->addItem(balas.last());
                        }

            }

            if(data=='O')//salir
            {
                delete this;
            }


            if(data=='X')//detener las occiones de las actividades anteriores
            {
                jugador->setVx(0);
                if(!jugador->getVy()!=0)
                {
                    jugador->setVy(jugador->getVy()-g);
                }
                flag3 = false;
                flag = false;
            }
         }// Movimiento bluetooht fin

    //Lo mismo de actualizacion battle


    for(int i=0;i< obstaculos.length();i++)
    {
        if(jugador->collidesWithItem(obstaculos.at(i)))
        {
            q2= abs((jugador->getPy()-jugador->getCheigh())-(obstaculos.at(i)->getPy()+obstaculos.at(i)->getCheigh()));
            if(!flag3)//es false cuando no se presiona w
            {
                banCoy = true;
                jugador->detectarChoque(jugador,obstaculos.at(i));
            }break;
        }
    }
    for(int i =0;i<cosas.length();++i)
    {
        h = cosas.at(i)->getPy()-cosas.at(i)->getCheigh()-(jugador->getPy()+jugador->getCheigh());
        if(cosas.at(i)->collidesWithItem(jugador))
        {
            if(h>=-1.50){
                if(!flag)
                {
                    banCcy = true;
                    jugador->detectarpiso(jugador,cosas.at(i));
                }
            }break;
        }
    }
    if(banCcy==false && banCoy==false)//condicional significa que los dos no estan colisionando
    {
        jugador->setAy(g);
    }
    else
    {
        jugador->setAy(0);
    }
    banCcy = banCoy = false;

    jugador->mover();

    for(int i=0;i<enemigos.length();i++)
    {
        enemigos.at(i)->moveEnemigos();
        for(int j =0; j<VidasEnemigos.at(i).length();j++)
            VidasEnemigos.at(i).at(j)->setPos(enemigos.at(i)->getPx()+(j*10)-posV,enemigos.at(i)->getPy()-40);
    }
    for(int i =0; i<monedas.length();i++)
    {
        if(jugador->collidesWithItem(monedas[i]))
        {
            if(abs(jugador->getPx()-monedas[i]->getPx())<10)
            {
                puntaje++;
                scene->removeItem(monedas[i]);
                monedas.removeAt(i);
            }
        }
    }
    //veriicacion para pasar de nivel

    if(jugador->collidesWithItem(puertas.last()) && enemigos.isEmpty())
    {

        menu *volver = new menu();
        volver->setNombres(nombres);

           nivelJugador++;

        if(nivelJugador>9)
        {
            nivelJugador = 9;
        }
        volver->setNivel(nivelJugador);
        if(volver->getNivel()==2)volver->bloqueo2();
        if(volver->getNivel()==3)volver->bloqueo3();
        if(volver->getNivel()==4)volver->bloqueo4();
        if(volver->getNivel()==5)volver->bloqueo5();
        if(volver->getNivel()==6)volver->bloqueo6();
        if(volver->getNivel()==7)volver->bloqueo7();
        if(volver->getNivel()==8)volver->bloqueo8();
        if(volver->getNivel()==9)volver->bloqueo9();
        obtenerusuarios();
        volver->setPuntaje(obtenerPuntaje());
        volver->show();
        delete this;
    }
}
void niveles::upScene()//
{
    x = jugador->getPx()-jugador->getCwidth()-300;//posicion de movimiento de la escena x
    y = jugador->getPy()+jugador->getCheigh()-250;//posicion de movimiento en la escen en y
    scene->setSceneRect(x+cont,y,scene->width(),scene->height());
    xv = jugador->getPx()-40;//posicion de las vidas en x
    yv = jugador->getPy()-65;//posicion de las vidas en y
    for(int i =0; i<vidas.length();i++)
    {
        vidas.at(i)->setPos(xv+(i*10),yv);//agrega las vidas
    }

    for(int i =0;i<salud.length();i++)
    {
        if(vidas.length()<10 && jugador->collidesWithItem(salud[i]))//rellena las vidas del jugador
        {
            if(abs(jugador->getPx()-salud[i]->getPx())<=15)
            {
                while(vidas.length()<10)
                {
                    vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
                    scene->addItem(vidas.last());

                }

                scene->removeItem(salud[i]);
                salud.removeAt(i);
            }
        }
    }

}

float niveles::CalCantidadD()//suma los pixeles que se corre, meve la escena a la derecha
{
    if(cont<0)
        cont+=3;
    vderecha=true;
    return cont;
}
float niveles::CalCantidadA()//la mueve hacia la izquierda
{
    if(cont>-400)
        cont-=3;
    vderecha=false;
    return cont;
}

bool niveles::Sumaux()//cabio de direccion
{
    if(flagDir == flagDirAnt)
    {
        m = false;
    }
    else
    {
        m =  true;
        flagDirAnt = flagDir;
    }
    return m;
}

void niveles::moVbalas()//battle
{

    if(balas.length()==0)
    {
        disbala = true;
    }
    for(int i =0;i<balas.length();i++)
    {
        balas.at(i)->movBala();
        QList <QGraphicsItem *> colliding_items = balas.at(i)->collidingItems();
        for(int j=0;j<colliding_items.size();j++){
            if(typeid(*(colliding_items[j]))==typeid(objetos)||typeid(*(colliding_items[j]))==typeid(player)){
                scene->removeItem(balas.at(j));
                balas.removeOne(balas.at(j));
                if(balas.isEmpty())
                {
                    balas.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                    scene->addItem(balas.last());
                }
                for(int i =0;i<enemigos.length();i++)//verifica para restar las vidas de enemigos
                {
                    if(colliding_items[j]==enemigos.at(i))
                    {
                        if(!(VidasEnemigos[i].isEmpty()))
                        {
                            scene->removeItem(VidasEnemigos[i].last());
                            VidasEnemigos[i].removeLast();

                        }
                        else if(VidasEnemigos[i].isEmpty())//s esta vaci eleminelo
                        {
                            VidasEnemigos.removeAt(i);
                            scene->removeItem(enemigos.at(i));
                            enemigos.removeAt(i);
                            break;
                        }
                        scene->removeItem(balas.at(j));
                        balas.removeOne(balas.at(j));
                        enemigos.at(i)->setVidas(enemigos.at(i)->getVidas()-1);
                        if(balas.length()==0)
                        {
                            balas.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                            scene->addItem(balas.last());
                        }
                    }
                }
                if(balas.isEmpty())//machetazo
                {
                    balas.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                    scene->addItem(balas.last());
                }
                if(!vidas.isEmpty())
                {
                    if(typeid(*(colliding_items[j]))==typeid(player))//suicidio
                    {
                        scene->removeItem(balas.at(j));
                        balas.removeOne(balas.at(j));
                        scene->removeItem(vidas.at(vidas.length()-1));
                        vidas.removeAt(vidas.length()-1);
                    }
                }
                if(balas.isEmpty())//machetazos
                {
                    balas.append(new objetos(-20050,20050,50,50,0,":/imagenes/naoko.png",Qt::red));
                    scene->addItem(balas.last());
                }
                return;
            }
        }
    }
}

void niveles::verificacion()//verifica si los enemigos nos golpean
{
    for(int i=0;i<enemigos.length();i++)//recorrer la lsita de enemigo
    {
        if(jugador->collidesWithItem(enemigos.at(i)))
        {
            scene->removeItem(vidas.last());
            vidas.removeLast();
        }
        if(vidas.isEmpty())//si la vida esta vacia,se murio
        {
            Tveri->stop();//para este slot y crea un nuevo esceario con otras condiciones similares
            niveles *escenarios = new niveles();
            escenarios->deleteLater();
            escenarios->setNombres(nombres);//pasa el nombre para la base de datos
            escenarios->objetosN1();
            escenarios->actualizacion();
            escenarios->show();
            scene->removeItem(jugador);
            jugador = new player(0,500,50,70,":/imagenes/cuadrado.jpg");
            scene->addItem(jugador);
            ui->graphicsView->setFocus();
            for(int i=0;i<10;i++)
            {
                vidas.append(new objetos(0,0,10,4,":/imagenes/jugador 2.0/vidas/vidaJugador.png",Qt::green));
                scene->addItem(vidas.last());
            }
            reinicio=true;
        }
        if(reinicio==true)//vueve a inicia el timer para poder volver a juga
        {
            Tveri->start(200);
        }
    }
}


QString niveles::getNombres() const
{
    return nombres;
}

void niveles::setNombres(const QString &value)
{
    nombres = value;
}
void niveles::mousePressEvent(QMouseEvent *ev)
{
    mpos = ev->pos();
}

void niveles::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton)
    {
        QPoint diff = ev->pos() - mpos;
        QPoint newpos = this->pos() + diff;
        this->move(newpos);
    }
}

void niveles::creartablacaracteristicas()
{

        QString consulta;
        consulta.append("CREATE TABLE IF NOT EXISTS datosUsuarios("//crea una tabla
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "nombre VARCHAR(100),"
                        "nivel INTEGER NOT NULL,"
                        "puntaje INTEGER NOT NULL"
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

void niveles::insertarvalores()
{

    QString consulta; //string de consulta para insertar el usuario a la base de datos
    QSqlQuery insertar;// consulta que inserta en la base de datos el usuario y la contraseña creadas


    consulta.append("INSERT INTO datosUsuarios("
                    "nombre,"
                    "nivel,"
                    "puntaje)"
                    " VALUES("
                    "'"+nombres+"',"
                    +QString::number(nivelJugador)+","
                    +QString::number(puntaje)+");"
                    );
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

}

int niveles::obtenerNivel()
{

        QString consulta;
        consulta.append("SELECT nivel FROM datosUsuarios WHERE nombre='"+nombres+"';");
        QSqlQuery consultar;
        consultar.prepare(consulta);

        if(consultar.exec())
        {
            consultar.next();
            qDebug()<<"retornó";
            return consultar.value(0).toInt();
        }
        else
        {
            qDebug()<<"no retornó";
            qDebug()<<"ERROR !"<<consultar.lastError();
            return NULL;
        }
}

void niveles::actualizarvalores()
{

    QString consulta; //string de consulta para insertar el usuario a la base de datos
    QSqlQuery insertar;// consulta que inserta en la base de datos el usuario y la contraseña creadas

    consulta.append("UPDATE datosUsuarios SET "
                    "nivel="+QString::number(nivelJugador)+","
                    "puntaje="+QString::number(puntaje+obtenerPuntaje())+" "
                    "WHERE nombre='"+nombres+"';"
                    );

    insertar.prepare(consulta);
       if(insertar.exec())
       {
           qDebug()<<"se actualizó";
       }
       else
       {
           qDebug()<<"no se actualizó";
           qDebug()<<"ERROR !"<<insertar.lastError();
       }

}

int niveles::obtenerPuntaje()
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

void niveles::obtenerusuarios()
{
    QString consulta;
    consulta.append("SELECT * FROM datosUsuarios GET WHERE nombre='"+nombres+"'");

    QSqlQuery consultar;
    consultar.prepare(consulta);

    if(consultar.exec())
    {
        qDebug()<<"se consulto";
        if(consultar.at()==-1)
        {
            actualizarvalores();
        }
        else
        {
            insertarvalores();
        }
    }
    else
    {
        qDebug()<<"no se consulto";
        qDebug()<<"ERROR !"<<consultar.lastError();
    }

}


void niveles::keyPressEvent(QKeyEvent *ev)
{

    if(ev->key()==Qt::Key_F1)
    {
        menu *volver = new menu();
        volver->setNombres(nombres);
        volver->setNivel(obtenerNivel());
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
    if(ev->key()==Qt::Key_F2)
    {
        delete this;
    }
    if(ev->key()==Qt::Key_F3)
    {
        obtenerusuarios();

    }
    if(ev->key()==Qt::Key_F4)
    {

        obtenerNivel();
    }

    if(ev->key()==Qt::Key_J)
    {   if(disbala)
        {
            balas.append(new objetos(jugador->getPx(),jugador->getPy(),40,12,300,":/imagenes/laser1.png",Qt::black,vderecha));
            scene->addItem(balas.last());
            disbala = false;
        }
        if(abs(balas.last()->getPx()-jugador->getPx())>150)
        {
            balas.append(new objetos(jugador->getPx(),jugador->getPy(),40,12,300,":/imagenes/laser1.png",Qt::black,vderecha));
            scene->addItem(balas.last());
        }
    }

    if(ev->key()==Qt::Key_W)
    {
        if(jugador->getPy()==500-jugador->getCheigh()){
            jugador->setVy(-300);
        }

        for(int i =0;i<cosas.length();++i)
        {
            if(jugador->collidesWithItem(cosas.at(i)))
            {
                flag = true;

                jugador->setVy(-300);
                break;
            }
        }
        for(int i =obstaculos.length()-1;i>=0;i--)
        {
            if(jugador->collidesWithItem(obstaculos.at(i)))
            {
                if(q2<4.0)
                {
                    flag3 = false;
                    jugador->setVy(300);
                }
                else
                {
                    flag3 = true;
                    jugador->setVy(-300);
                }
            }
        }
    }
    else if(ev->key()==Qt::Key_S)
    {
        jugador->setVy(200);
        flag = true;
    }
    else if(ev->key()==Qt::Key_D)
    {
        flag3 = false;
        Ta->stop();
        flagDir = 1;
        if(Sumaux())
        {
            if(cont>0)
                cont =0;
            Td->start(2);
        }
        jugador->setVx(180);
    }
    if(ev->key()==Qt::Key_A)
    {
        flag3 = false;
        Td->stop();
        flagDir = 0;
        if(Sumaux())
        {
            if(cont<-399)
                cont =0;
            Ta->start(2);
        }
        jugador->setVx(-180);
    }
}

void niveles::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_D||ev->key()==Qt::Key_A)
    {
        jugador->setVx(0);
    }
    if(ev->key()==Qt::Key_S)
    {
        flag = false;
    }
    if(ev->key()==Qt::Key_W)
    {   flag3 = false;
        flag = false;
    }
}


